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

const Value &Record::info(const std::string &name)
{

    return mInfos.at(name);

}

const Value &Record::format(const std::string &name, int sample)
{
    return mSampleFormats.at(sample).at(name);
}

//const vector<string, Value> &Record::infos() const
//{
//    return mInfos;
//}

//const vector<string, Value> &Record::formats() const
//{
//    return mFormats;
//}

