#include <string>
#include <iostream>
#include <fstream>
#include <regex>

#include "vcfreader.h"

using namespace std;


const std::unordered_map<std::string, Value::Type> VcfReader::StringType = {
    {"String", Value::String},
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

            Header header = Header{
                    info_match[1].str(), // Header Type
                    info_match[2].str(), // ID
                    1, // NUMBER
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
        type = StringType.at(name);
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
    bool success = bool(getline(*mFile, mCurrentLine));
    if (success)
    {
        readRecord();
        return true;
    }

    return false;
}
////--------------------------------------------------

const Record &VcfReader::record() const
{
    return mCurrentRecord;
}
////--------------------------------------------------

void VcfReader::readRecord()
{

    stringstream line(mCurrentLine);
    vector<string> fields;

    string item;
    while (getline(line, item, '\t'))
        fields.push_back(item);

    mCurrentRecord.mChrom = fields[0];
    mCurrentRecord.mPos = stol(fields[1]);
    mCurrentRecord.mId = fields[2];
    mCurrentRecord.mRef = fields[3];
    mCurrentRecord.mAlt = fields[4];
    mCurrentRecord.mQual = fields[5];
    mCurrentRecord.mFilter = fields[6];

    // Fill bool type with false value
    for (const auto& info : mFlagInfos)
        mCurrentRecord.mInfos[info] = Value("0", Value::Bool, 1);

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
                uint number = mInfos[_key].number;
                mCurrentRecord.mInfos[_key] = Value(value,info_type, number);
            }

            else
                mCurrentRecord.mInfos[info] = Value("1", Value::Bool, 1);
        }

    }

        // Parse format field
        if (fields.size() > 9) {
            string format;
            stringstream format_tokens(fields.at(8));
            while (getline(format_tokens, format,':')){
                mCurrentRecord.mFormats.push_back(format);
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

                    auto key = mCurrentRecord.mFormats[format_index];
                    auto type = this->format(key).type;

                    sample_format[key] = Value(sample_value, type);

                    format_index++;
                }
                mCurrentRecord.mSampleFormats.push_back(sample_format);
            }
        }
}


