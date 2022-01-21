#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <locale>
#include <fstream>

namespace utils{

bool isNumber(const std::string& str);

std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);
bool file_exists (const std::string& name);

};



#endif // UTILS_H
