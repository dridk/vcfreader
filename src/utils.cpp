#include "utils.h"

namespace utils{

bool isNumber(const std::string& str){
    try {
        std::stod(str);
        return true;
    }

    catch (const std::exception& )
    {
        return false;
    }
}

std::string toLower(const std::string &str)
{
    std::string data = str;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return data;
}

std::string toUpper(const std::string &str)
{
    std::string data = str;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::toupper(c); });
    return data;
}


bool file_exists (const std::string& name) {
    std::fstream f(name.c_str());
    return f.good();
}

std::vector<std::string> split(const std::string &str, char sep)
{
    std::stringstream f(str);
    std::string s;
    std::vector<std::string> results;
     while (getline(f, s, sep)) {
         results.push_back(s);
     }

     return results;
}



};


