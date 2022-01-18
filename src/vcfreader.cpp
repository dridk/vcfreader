#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "vcfreader.h"

using namespace std;


//=============== TOOLS =============================
bool is_digit(const string& str){
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }

    return true;

}
//=============== VcfReader =============================

VcfReader::VcfReader(const string &filename)
    : mFilename(filename), mStartOffset(0)
{

    mFile = new zstr::ifstream(filename, ios::binary);
    readHeader();
}

//--------------------------------------------------

const Header &VcfReader::get_info(const string &key)
{

    return mInfos.at(key);
}

//--------------------------------------------------

const Header &VcfReader::get_format(const string &key)
{
    return mFormats.at(key);
}

//--------------------------------------------------

VcfReader* VcfReader::__iter__(){

    return this;
}
//--------------------------------------------------

const Record& VcfReader::__next__(){

    next();
    return record();
}
//--------------------------------------------------

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
//--------------------------------------------------

const Record &VcfReader::record() const
{

    return mCurrentRecord;
}
//--------------------------------------------------

const vector<string> &VcfReader::get_samples()
{
    return mSamples;
}
//--------------------------------------------------

void VcfReader::readRecord()
{

    stringstream line(mCurrentLine);
    vector<string> fields;

    string item;
    while (getline(line, item, '\t'))
        fields.push_back(item);

    mCurrentRecord.chrom = fields[0];
    mCurrentRecord.pos = stol(fields[1]);
    mCurrentRecord.id = fields[2];
    mCurrentRecord.ref = fields[3];
    mCurrentRecord.alt = fields[4];
    mCurrentRecord.qual = fields[5];
    mCurrentRecord.filter = fields[6];

    //Parse info field for this record
    if (fields.size() > 7){
        string info;
        stringstream info_tokens(fields.at(7));
        while (getline(info_tokens, info, ';'))
        {
            size_t delim_pos = info.find('=');
            string _key = info.substr(0, delim_pos);
            string value = info.substr(delim_pos + 1, string::npos);
            string info_type = mInfos[_key].type;
            uint dim = mInfos[_key].dim;

            mCurrentRecord.infos[_key] = Value{dim, info_type, _key, value};
        }

    }

    // Parse format field
    if (fields.size() > 9) {
        string format;
        stringstream format_tokens(fields.at(8));
        while (getline(format_tokens, format,':')){
            mCurrentRecord.format_names.push_back(format);
        }

        // parse samples
        for (uint i = 9 ; i<fields.size(); ++i)
        {
            stringstream sample_tokens(fields.at(i));
            string sample_value;
            map<string,Value> sample_data;
            int format_index=0;

            while (getline(sample_tokens, sample_value,':')){

                auto key = mCurrentRecord.format_names[format_index];
                auto format = mFormats[key];
                sample_data[key] = Value{format.dim,format.type, key, sample_value};
                format_index++;

            }

            mCurrentRecord.formats.push_back(sample_data);

        }
    }
}
//--------------------------------------------------

void VcfReader::readHeader()
{

    string line;
    const regex info_format_regexp("##(\\w+)=<ID=([^,]+)\\s*,Number=([^,]+)\\s*,Type=([^,]+)\\s*,Description=\"([^\"]+)\">");
    const regex filter_regexp("##FILTER=<ID=([^,]+)\\s*,Description=\"([^\"]+)\">");
    const regex sample_regexp("^#CHROM.+FORMAT\\t(.+)");

    while (getline(*mFile, line))
    {

        if (line.substr(0, 1) != "#")
        {
            break;
        }

        // Parse INFO columns
        smatch info_match;
        if (regex_search(line, info_match, info_format_regexp))
        {

            auto header_type = info_match[1];
            auto header_id = info_match[2];

            string dimension = info_match[3].str();

            Header header = Header{
                    info_match[1].str(), // Header Type
                    info_match[2].str(),
                    1,
                    info_match[4].str(), // TYPE
                    info_match[5].str(), // DESCRIPTION
        };

        if (header_type == "FORMAT")
            mFormats[header_id] = header;

        if (header_type == "INFO")
            mInfos[header_id] = header;
    }
    // Parse SAMPLE columns

    smatch sample_match;
    if (regex_search(line, sample_match, sample_regexp))
    {

        cout<<line<<endl;
        auto sample_names = sample_match[1];
        stringstream all_samples(sample_names.str());

        string sampleName;
        while (getline(all_samples, sampleName, '\t'))
        {
            mSamples.push_back(sampleName);
        }
    }
}
}

//--------------------------------------------------

vector<string> VcfReader::infos() const
{
    vector<string> retval;
    for (auto const& element : mInfos) {
        retval.push_back(element.first);
    }

    return retval;
}
vector<string> VcfReader::formats() const
{
    vector<string> retval;
    for (auto const& element : mFormats) {
        retval.push_back(element.first);
    }

    return retval;

}
//=============== Record =============================

vector<string> Record::get_info_keys() const
{
    vector<string> retval;
    for (auto const& element : infos) {
        retval.push_back(element.first);
    }

    return retval;
}

vector<string> Record::get_format_keys() const
{
    return format_names;
}

const Value &Record::get_info(const string &key) const
{
    return infos.at(key);
}

const Value &Record::get_format(int index, const string& key) const
{
    return formats[index].at(key);
}



