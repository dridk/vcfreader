#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <vector>
#include "value.h"

class Value;
class Record;

class Record
{
public:
    Record();

    const std::string &chrom() const;
    unsigned long pos() const;
    const std::string &id() const;
    const std::string &ref() const;
    const std::string &alt() const;
    const std::string &qual() const;
    const std::string &filter() const;

    static Record from_line(const std::string& line);




private:
    std::string mChrom;
    unsigned long mPos;
    std::string mId;
    std::string mRef;
    std::string mAlt;
    std::string mQual;
    std::string mFilter;
    std::map<std::string, Value> mInfos;
    std::map<std::string, Value> mFormats;


};

#endif // RECORD_H
