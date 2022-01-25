#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <locale>
#include <vector>
#include <sstream>
#include <fstream>

namespace utils{

bool isNumber(const std::string& str);

std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);
bool file_exists (const std::string& name);

std::vector<std::string> split(const std::string& str, char sep);

template <typename T>
bool contains(const std::vector<T>& c, const T& key ){
    return std::find(c.begin(), c.end(), key) != c.end();
}

};



#endif // UTILS_H
