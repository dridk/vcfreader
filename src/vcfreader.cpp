#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "vcfreader.h"

using namespace std;

VcfReader::VcfReader(const string &filename)
    : mFilename(filename), mStartOffset(0)
{

  mFile = new zstr::ifstream(filename, ios::binary);
  readHeader();
}

const Header &VcfReader::get_info(const string &key)
{

  return mInfos.at(key);
}

const Header &VcfReader::get_format(const string &key)
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

const Record &VcfReader::record() const
{

  return mCurrentRecord;
}

const vector<string> &VcfReader::get_samples()
{
  return mSamples;
}

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
  string info;
  stringstream info_tokens(fields.at(7));
  while (getline(info_tokens, info, ';'))
  {
    size_t delim_pos = info.find('=');
    string _key = info.substr(0, delim_pos);
    string value = info.substr(delim_pos + 1, string::npos);
    string info_type = mInfos[_key].type;
    mCurrentRecord.infos[_key] = Value{info_type, _key, value};
  }
}

void VcfReader::readHeader()
{

  string line;
  const regex info_format_regexp("##(\\w+)=<ID=([^,]+)\\s*,Number=([^,]+)\\s*,Type=([^,]+)\\s*,Description=\"([^\"]+)\">");
  const regex filter_regexp("##FILTER=<ID=([^,]+)\\s*,Description=\"([^\"]+)\">");
  const regex sample_regexp("^#CHROM.+FORMAT\\s*(\\S.+)$");

  while (getline(*mFile, line))
  {

    if (line.substr(0, 1) != "#")
    {
      cout << "Fin\n";
      break;
    }

    // Parse INFO columns
    smatch info_match;
    if (regex_match(line, info_match, info_format_regexp))
    {

      auto header_type = info_match[1];
      auto header_id = info_match[2];

      Header header = Header{
          info_match[1].str(), // Header Type
          info_match[2].str(), // ID
          info_match[3].str(), // NUMBER
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
    if (regex_match(line, sample_match, sample_regexp))
    {

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

const Value &Record::get_info(const string &key) const
{
  return infos.at(key);
}
