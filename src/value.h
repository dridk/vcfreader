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
public:
    enum Type{
        String,
        Integer,
        Double,
        Bool,
        None
    };

    Value(const std::string& value = std::string(),
          Type type = Type::String,
          uint dim = 1);

    int toInt() const;
    double toDouble() const;
    bool toBool() const;

    const std::string& toString() const;

    std::vector<Value> toList() const;




    Type type() const;

     std::string type_name() const;

private:
    std::string mKey;
    std::string mValue;
    Type mType;
    uint mDim;

    //const static std::unordered_map<Value::Type, std::string> TypeNames;

};

#endif // VALUE_H
