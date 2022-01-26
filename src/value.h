#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cctype>

#include "utils.h"

class Value
{

    /*!
  * @class Value
  * @brief The Type enum
  *
  * This is a generic class used to store values with unknown types like QVariant.
  * It is intended to expose C++ value to Python.
  *
  * @example
  *    Value value("343");
  *    int a = value.to_int();
  *
  *    Value value("32,234", Value::Integer, 2);
  *    for (auto v : value.to_list())
  *       int a = v.to_int()

*/

public:
    enum Type{
        String,
        Integer,
        Double,
        Bool,
        Invalid
    };

    Value(const std::string& value = std::string(),
          Type type = Type::String,
          unsigned int dim = 1);

    Value(long value);
    Value(double value);
    Value(float value);
    Value(bool value);

    //Conversion function
    int to_int() const;
    double to_double() const;
    bool to_bool() const;
    const std::string& to_string() const;
    std::vector<Value> to_list() const;


    Type type() const;
    std::string type_name() const;
    unsigned int dim() const;

private:
    std::string mKey;
    std::string mValue;
    Type mType;
    unsigned int mDim;

};

#endif // VALUE_H
