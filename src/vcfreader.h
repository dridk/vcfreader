#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <zstr.hpp>
#include <sstream>
#include <queue>
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
    string number;
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

protected:
    void parse_header();
    Record parse_record(int alt_index = 0);
    static Value::Type type_from_string(const std::string& name);


private:

    int count_alt();


    string mCurrentLine;
    Record mCurrentRecord;
    string mFilename;
    unordered_map<string, Header> mFormats;
    unordered_map<string, Header> mInfos;
    unordered_map<string, Header> mFilter;
    vector<string> mSamples;

    vector<string> mFlagInfos;

    queue<Record> mRecordsQueue;

    static const std::unordered_map<std::string, Value::Type> StringToTypeMap;


    zstr::ifstream *mFile;
    uint64_t mStartLine;
};
