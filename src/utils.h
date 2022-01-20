#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <locale>

namespace utils{

bool isNumber(const std::string& str);

std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);

};



#endif // UTILS_H
