#include <string>
#include <iostream>
#include <fstream>
#include <zstr.hpp>
#include "vcfreader.h"

using namespace std;

VcfReader::VcfReader(const string& filename)
:mFilename(filename)
{

  cout<<"CONSTRUCTION"<<mFilename<<endl;
}

bool VcfReader::next()
{


return false;
}

int VcfReader::value() const
{

  return 43;


}

void VcfReader::test() const
{


 zstr::ifstream file(mFilename,ios_base::in | ios_base::binary);
 string line;
 if (file.is_open()) {

  while (getline(file, line))
  {
    std::cout << line << std::endl;
  }

}

}
