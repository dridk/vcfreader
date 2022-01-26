#include "record.h"

Record::Record()
{}


const std::string &Record::chrom() const
{
    return mChrom;
}

unsigned long Record::pos() const
{
    return mPos;
}

const std::string &Record::id() const
{
    return mId;
}

const std::string &Record::ref() const
{
    return mRef;
}

const std::string &Record::alt() const
{
    return mAlt;
}

const std::string &Record::qual() const
{
    return mQual;
}

const std::string &Record::filter() const
{
    return mFilter;
}

const Value &Record::info(const std::string &name) const
{

        return mInfos.at(name);



}

const Value &Record::format(const std::string &name, int sample) const
{
    return mSampleFormats.at(sample).at(name);
}

std::vector<std::string> Record::info_keys() const
{
    return utils::get_keys(mInfos);
}

std::vector<std::string> Record::format_keys() const
{
    return mFormats;

}

//const vector<string, Value> &Record::infos() const
//{
//    return mInfos;
//}

//const vector<string, Value> &Record::formats() const
//{
//    return mFormats;
//}

