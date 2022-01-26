#include <string>
#include <iostream>
#include <fstream>
#include <regex>

#include "vcfreader.h"

using namespace std;


const std::unordered_map<std::string, Value::Type> VcfReader::StringToTypeMap = {
    {"String", Value::String},
    {"Character", Value::String},
    {"Integer", Value::Integer},
    {"Flag", Value::Bool},
    {"Float", Value::Double}
};


//=============== VcfReader =============================

VcfReader::VcfReader(const string &filename)
    : mFilename(filename), mStartLine(0)
{

    std::setlocale(LC_ALL, "en_US.UTF-8");
    mFile = new zstr::ifstream(filename, ios::binary);
    parse_header();

}

void VcfReader::parse_header()
{
    string line;
    const regex info_format_regexp("##(\\w+)=<ID=([^,]+)\\s*,Number=([^,]+)\\s*,Type=([^,]+)\\s*,Description=\"([^\"]+)\">");
    const regex filter_regexp("##FILTER=<ID=([^,]+)\\s*,Description=\"([^\"]+)\">");
    const regex sample_regexp("^#CHROM.+FORMAT\\t(.+)");

    while (getline(*mFile, line))
    {
        mStartLine ++;
        smatch info_match;
        if (regex_search(line, info_match, info_format_regexp))
        {

            string dimension = info_match[3].str();
            string number = info_match[3];

            Header header = Header{
                    info_match[1].str(), // Header Type
                    info_match[2].str(), // ID
                    info_match[3].str(), // NUMBER
                    type_from_string(info_match[4].str()), //TYPE
                    info_match[5].str() // DESCRIPTION
        };

        if (header.headerType == "FORMAT")
            mFormats[header.id] = header;

        if (header.headerType == "INFO")
            mInfos[header.id] = header;

        if (header.headerType == "INFO" && header.type == Value::Bool)
            mFlagInfos.push_back(header.id);
    }
    // Parse SAMPLE columns
    smatch sample_match;
    if (regex_search(line, sample_match, sample_regexp))
    {
        auto sample_names = sample_match[1];
        stringstream sample_names_ss(sample_names.str());

        mSamples = utils::split(sample_names.str(),'\t');
        break;
    }
}
}

Value::Type VcfReader::type_from_string(const string &name)
{
    Value::Type type;
    try {
        type = StringToTypeMap.at(name);
    }  catch (std::out_of_range) {

        type = Value::String;
    }

    return type;
}


const vector<string> &VcfReader::samples()
{
    return mSamples;
}

vector<string> VcfReader::info_keys() const
{
    return utils::get_keys(mInfos);
}
vector<string> VcfReader::format_keys() const
{
    return utils::get_keys(mFormats);
}

const Header &VcfReader::info(const string &key)
{
    return mInfos.at(key);
}

//--------------------------------------------------

const Header &VcfReader::format(const string &key)
{

    return mFormats.at(key);

}

bool VcfReader::next()
{
    string line;
    bool success = false;

    if (mRecordsQueue.empty())
    {
        success = bool(getline(*mFile, mCurrentLine));
        if (!success)
            return false;

        for (int i=0; i<count_alt(); i++)
            mRecordsQueue.push(parse_record(i));
    }

    mCurrentRecord = mRecordsQueue.front();
    mRecordsQueue.pop();



    return true;
}
////--------------------------------------------------

const Record &VcfReader::record() const
{
    return mCurrentRecord;
}
////--------------------------------------------------

Record VcfReader::parse_record(int alt_index)
{
    Record record;
    vector<string> fields = utils::split(mCurrentLine, '\t');

    record.mChrom = fields[0];
    record.mPos = stol(fields[1]);
    record.mId = fields[2];
    record.mRef = fields[3];
    record.mAlt = utils::split(fields[4],',')[alt_index];
    record.mQual = fields[5];
    record.mFilter = fields[6];

    for (const auto& info : mFlagInfos)
        record.mInfos[info] = Value(false);

    //Parse info field for this record
    if (fields.size() > 7){

        for (const string& info : utils::split(fields.at(7),';'))
        {
              // Example DP=5 with DP as Integer with Number = 1
            size_t delim_pos = info.find('=');

            if (delim_pos == string::npos) // no symbol "=" . It is a flag
                record.mInfos[info] = Value(true);

            else
            {
                string key = info.substr(0, delim_pos); // key = DP
                string value = info.substr(delim_pos + 1, string::npos); // value = 5
                Value::Type info_type = mInfos[key].type; // type = Integer
                string number = mInfos[key].number; // Number = 1

                // get dimension number : 1 as default
                uint dim = utils::is_number(number) ? stoi(number) : 1;

                if (number == "A")
                    value = utils::split(value,',')[alt_index];

                if (number == "R"){
                    auto list_val = utils::split(value,',');
                    value = list_val[0] + "," + list_val[alt_index+1];
                }

                if (number == "." || number == "G")
                    dim = utils::split(value,',').size();


                record.mInfos[key] = Value(value,info_type, dim);
            }
        }
    }

    // Parse samples !
    if (fields.size() >= 10) {
        // parse format
        record.mFormats = utils::split(fields.at(8),':');
        // Loop over samples
        for (uint i = 9 ; i<fields.size(); ++i)
        {
            // Parse one sample
            SampleFormat sample_format; // store key:value

            // Loop over sample fields
            // 5:45:5324
            uint format_index = 0;
            for (auto& value: utils::split(fields.at(i),':'))
            {
                auto key = record.mFormats[format_index];
                Value::Type type = Value::String;
                string number = "1";

                // get dimension number : 1 as default
                uint dim = utils::is_number(number) ? stoi(number) : 1;

                try { type = this->format(key).type; } catch (...){};
                try { number = this->format(key).number; } catch (...){};

               if (number == "A") // 2,3
                   value = utils::split(value,',')[alt_index];

               if (number == "." || number == "G")
                   dim = utils::split(value,',').size();

                sample_format[key] = Value(value, type, dim);
            format_index++;
            }
            record.mSampleFormats.push_back(sample_format);
        }
    }

    return record;
}

int VcfReader::count_alt()
{
    stringstream line(mCurrentLine);
    string alt;

    // cut -f4
    int field_index = 0;
    while (getline(line, alt, '\t'))
    {
        if (field_index == 4)
            break;
        field_index++;
    }

    return std::count(alt.begin(), alt.end(), ',') + 1;

}


