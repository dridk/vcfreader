#include <string>
#include <iostream>
#include <fstream>
#include <zstr.hpp>
#include <regex>
#include "vcfreader.h"

using namespace std;


VcfReader::VcfReader(const string& filename)
:mFilename(filename)
{

  cout<<" IT WORKS "<<endl;
  readHeader();

}

const Header& VcfReader::get_info(const string& key)
{

  return mInfos.at(key);
}


const Header& VcfReader::get_format(const string& key)
{
  return mFormats.at(key);
}



void VcfReader::readHeader()
{
  zstr::ifstream file(mFilename);
  string line;
  const regex info_format_regexp("##(\\w+)=<ID=([^,]+)\\s*,Number=([^,]+)\\s*,Type=([^,]+)\\s*,Description=\"([^\"]+)\">");
  const regex filter_regexp("##FILTER=<ID=([^,]+)\\s*,Description=\"([^\"]+)\">");
  


  while (getline(file, line))
  {
    if (line.substr( 0, 2) != "##")
      break;


  // Parse INFO columns 
    smatch match;
    if (regex_match(line, match, info_format_regexp))
    {

      auto header_type = match[1];
      auto header_id = match[2];

      Header header = Header { 
        match[1].str(),    // Header Type  
        match[2].str(),  // ID 
        match[3].str(),  // NUMBER
        match[4].str(),  // TYPE
        match[5].str(),  // DESCRIPTION
      };

      if (header_type == "FORMAT")
        mFormats[header_id] = header;

      if (header_type == "INFO")
        mInfos[header_id] = header;
    }

  }





}




