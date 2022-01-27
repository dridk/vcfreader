#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <vector>
#include <unordered_map>
#include "value.h"

class Value;
class Record;
class VcfReader;

typedef std::unordered_map<std::string, Value> SampleFormat;

class Record
{
friend VcfReader;
public:
    Record();

    const std::string &chrom() const;
    unsigned long pos() const;
    const std::string &id() const;
    const std::string &ref() const;
    const std::string &alt() const;
    const std::string &qual() const;
    const std::string &filter() const;


    const Value& info(const std::string& name) const;
    const Value& format(const std::string& name, int sample=0) const;

    std::vector<std::string> info_keys() const;
    std::vector<std::string> format_keys() const;


private:
    std::string mChrom;
    unsigned long mPos;
    std::string mId;
    std::string mRef;
    std::string mAlt;
    std::string mQual;
    std::string mFilter;
    std::unordered_map<std::string, Value> mInfos;

    std::vector<std::string> mFormats;
    std::vector<SampleFormat> mSampleFormats;

    Value mNullValue;

};

#endif // RECORD_H
