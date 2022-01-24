#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <locale>
#include <vector>
#include <fstream>

namespace utils{

bool isNumber(const std::string& str);

std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);
bool file_exists (const std::string& name);

template <typename T>
bool contains(const std::vector<T>& c, const T& key ){
    return std::find(c.begin(), c.end(), key) != c.end();
}

};



#endif // UTILS_H
