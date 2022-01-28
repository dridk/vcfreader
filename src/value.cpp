#include "value.h"

const Value Value::none_value = Value("",Type::Invalid);

//--------------------------------------------------------------------
Value::Value( const std::string &value, Type type, unsigned int dim)
    :mValue(value),mType(type),mDim(dim)
{

    if ((value == ".") || (value == ""))
        mType = Type::Invalid;
}

Value::Value(long value)
{
    mType = Type::Integer;
    mDim = 1;
    mValue = std::to_string(value);
}

Value::Value(double value)
{
    mType = Type::Double;
    mDim = 1;
    mValue = std::to_string(value);
}

Value::Value(float value)
{
    mType = Type::Double;
    mDim = 1;
    mValue = std::to_string(value);
}

Value::Value(bool value)
{
    mType = Type::Bool;
    mDim = 1;
    mValue = std::to_string(value);
}


//--------------------------------------------------------------------
int Value::to_int() const
{
    if (utils::is_number(mValue))
        return std::stoi(mValue);

    std::cerr<<"Cannot convert to int \n";
    return 0;
}
//--------------------------------------------------------------------
double Value::to_double() const
{

    if (utils::is_number(mValue)){
        std::string s =  mValue;
        // replace , by .
        std::replace(s.begin(), s.end(), ',', '.');
        return std::stod(s.c_str());

    }
    std::cerr<<"Cannot convert to double \n";
    return 0;

}
//--------------------------------------------------------------------
bool Value::to_bool() const
{
    std::string value = utils::to_lower(mValue);

    if (value == "0" || value == "1")
        return bool(std::stoi(mValue));

    if (value == "true")
        return true;

    if (value =="false")
        return false;


    std::cerr<<"Cannot convert to double \n";
    return 0;
}

//--------------------------------------------------------------------
const std::string &Value::to_string() const
{
    return mValue;
}
//--------------------------------------------------------------------
std::vector<Value> Value::to_list() const
{
    std::vector<Value> results;
    std::stringstream st(mValue);
    std::string line;
    while (getline(st, line, ','))
        results.push_back(Value(line, mType));

    return results;

}

const Value &Value::none()
{
    return Value::none_value;
}
//--------------------------------------------------------------------
Value::Type Value::type() const
{
    return mType;
}
//--------------------------------------------------------------------
std::string Value::type_name() const
{
    if (mType == Value::String)
        return "String";
    if (mType == Value::Integer)
        return "Integer";
    if (mType == Value::Double)
        return "Double";
    if (mType == Value::Bool)
        return "Bool";
    if (mType == Value::Invalid)
        return "Invalid";

    return "Invalid";
}
//--------------------------------------------------------------------
unsigned int Value::dim() const
{
    return mDim;
}



