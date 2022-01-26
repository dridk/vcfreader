#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <locale>
#include <vector>
#include <sstream>
#include <fstream>

namespace utils{
/**
 * A Set of useful function unavaible from C++ standard library
*/

/**
 * @brief isNumber
 * @param str
 * @return true if string is a number
 */
bool is_number(const std::string& str);

/**
 * @brief toLower
 * @param str
 * @return Lower string
 */
std::string to_lower(const std::string& str);

/**
 * @brief to_upper
 * @param str
 * @return Upper string
 */
std::string to_upper(const std::string& str);

/**
 * @brief file_exists
 * @param name
 * @return true if file exists. Otherwise return false
 */
bool file_exists (const std::string& filename);


std::vector<std::string> split(const std::string& str, char sep);

template <typename T>
bool contains(const std::vector<T>& c, const T& key ){
    return std::find(c.begin(), c.end(), key) != c.end();
}

};



#endif // UTILS_H
