#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <zstr.hpp>
#include <sstream>
#include "record.h"
using namespace std;

class VcfReader;
class Record;
struct Header;
class Value;

struct Header
{
    string headerType;
    string id;
    uint number;
    Value::Type type;
    string description;
};

class VcfReader
{

public:
    VcfReader(const string &filename);

    const Header &info(const string &key);
    const Header &format(const string &key);
    const vector<string> &samples();

    vector<string> info_keys() const;
    vector<string> format_keys() const;

    bool next();

    const Record& record() const;
    static Value::Type type_from_string(const std::string& name);

protected:
    void readHeader();
    void readRecord();


private:
    string mCurrentLine;
    Record mCurrentRecord;
    string mFilename;
    unordered_map<string, Header> mFormats;
    unordered_map<string, Header> mInfos;
    unordered_map<string, Header> mFilter;
    vector<string> mSamples;

    vector<string> mFlagInfos;


    static const std::unordered_map<std::string, Value::Type> StringType;

    zstr::ifstream *mFile;
    uint64_t mStartLine;
};
