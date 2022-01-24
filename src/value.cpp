#include "value.h"



Value::Value( const std::string &value, Type type, uint dim)
    :mValue(value),mType(type),mDim(dim)
{

}

int Value::toInt() const
{
    if (utils::isNumber(mValue))
        return std::stoi(mValue);

    std::cerr<<"Cannot convert to int \n";
    return 0;


}

double Value::toDouble() const
{

    if (utils::isNumber(mValue)){
        std::string s =  mValue;
        // replace , by .
        std::replace(s.begin(), s.end(), ',', '.');
        return std::stod(s.c_str());

    }
    std::cerr<<"Cannot convert to double \n";
    return 0;

}

bool Value::toBool() const
{
    std::string value = utils::toLower(mValue);

    if (value == "0" || value == "1")
        return bool(std::stoi(mValue));

    if (value == "true")
        return true;

    if (value =="false")
        return false;


    std::cerr<<"Cannot convert to double \n";
    return 0;}

const std::string &Value::toString() const
{
    return mValue;
}

std::vector<Value> Value::toList() const
{
    std::vector<Value> results;
    std::stringstream st(mValue);
    std::string line;
    while (getline(st, line, ','))
        results.push_back(Value(line, mType));

    return results;

}

Value::Type Value::type() const
{
    return mType;
}


