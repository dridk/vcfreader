#include <string>
#include <iostream>
#include <fstream>
#include <regex>

#include "vcfreader.h"

using namespace std;


const std::unordered_map<std::string, Value::Type> VcfReader::StringToTypeMap = {
    {"String", Value::String},
    {"Integer", Value::Integer},
    {"Flag", Value::Bool},
    {"Float", Value::Double}
};


const std::unordered_map<std::string, int> VcfReader::NumberToIntMap = {
    {".", 1},
    {"A", -1},
    {"G", -2},
    {"R", -3}
};

//=============== VcfReader =============================

VcfReader::VcfReader(const string &filename)
    : mFilename(filename), mStartLine(0)
{

    std::setlocale(LC_ALL, "en_US.UTF-8");
    mFile = new zstr::ifstream(filename, ios::binary);
    readHeader();

}

void VcfReader::readHeader()
{
    string line;
    const regex info_format_regexp("##(\\w+)=<ID=([^,]+)\\s*,Number=([^,]+)\\s*,Type=([^,]+)\\s*,Description=\"([^\"]+)\">");
    const regex filter_regexp("##FILTER=<ID=([^,]+)\\s*,Description=\"([^\"]+)\">");
    const regex sample_regexp("^#CHROM.+FORMAT\\t(.+)");

    while (getline(*mFile, line))
    {

        mStartLine ++;

        // Parse INFO columns
        smatch info_match;
        if (regex_search(line, info_match, info_format_regexp))
        {


            string dimension = info_match[3].str();

            string number = info_match[3];


            Header header = Header{
                    info_match[1].str(), // Header Type
                    info_match[2].str(), // ID
                    info_match[3].str(), // NUMBER
                    type_from_string(info_match[4].str()),
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
        stringstream all_samples(sample_names.str());

        string sampleName;
        while (getline(all_samples, sampleName, '\t'))
        {
            mSamples.push_back(sampleName);
        }

        //read header is now finished ..
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
    vector<string> retval;
    for (auto const& element : mInfos) {
        retval.push_back(element.first);
    }

    return retval;
}
vector<string> VcfReader::format_keys() const
{
    vector<string> retval;
    for (auto const& element : mFormats) {
        retval.push_back(element.first);
    }

    return retval;

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
            mRecordsQueue.push(readRecord(i));
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

Record VcfReader::readRecord(int alt_index)
{
    Record record;
    stringstream line(mCurrentLine);
    vector<string> fields;

    string item;
    while (getline(line, item, '\t'))
        fields.push_back(item);

    record.mChrom = fields[0];
    record.mPos = stol(fields[1]);
    record.mId = fields[2];
    record.mRef = fields[3];

    record.mAlt = utils::split(fields[4],',')[alt_index];

    record.mQual = fields[5];
    record.mFilter = fields[6];


    // Fill bool type with false value
    for (const auto& info : mFlagInfos)
        record.mInfos[info] = Value("0", Value::Bool, 1);

    //Parse info field for this record
    if (fields.size() > 7){
        string info;
        stringstream info_tokens(fields.at(7));
        while (getline(info_tokens, info, ';'))
        {

            size_t delim_pos = info.find('=');

            if (delim_pos != string::npos)
            {
                string _key = info.substr(0, delim_pos);
                string value = info.substr(delim_pos + 1, string::npos);
                Value::Type info_type = mInfos[_key].type;


                string number = mInfos[_key].number; // 1,2,3

                uint dim =1;
                if (utils::is_number(number))
                    dim = stoi(number);

                if (number == "A")
                    value = utils::split(value,',')[alt_index];

                if (number == ".")
                    dim = utils::split(value,',').size();


                record.mInfos[_key] = Value(value,info_type, dim);
            }

            else
                record.mInfos[info] = Value("1", Value::Bool, 1);
        }

    }

    // Parse format field
    if (fields.size() > 9) {
        string format;
        stringstream format_tokens(fields.at(8));
        while (getline(format_tokens, format,':')){
            record.mFormats.push_back(format);
        }

        // parse samples
        for (uint i = 9 ; i<fields.size(); ++i)
        {
            stringstream sample_tokens(fields.at(i));
            string sample_value;
            map<string,Value> sample_data;
            int format_index=0;

            SampleFormat sample_format;
            while (getline(sample_tokens, sample_value,':')){

                auto key = record.mFormats[format_index];

                Value::Type type = Value::String;
                string number = "1";

                try { type = this->format(key).type; } catch (...){};
                try { number = this->format(key).number; } catch (...){};


                sample_format[key] = Value(sample_value, type);

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


