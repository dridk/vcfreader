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

struct Header
{

    string HeaderType;
    string id;
    uint dim;
    string type;
    string description;
};

class VcfReader
{

public:
    VcfReader(const string &filename);

    const Header &get_info(const string &key);
    const Header &get_format(const string &key);
    const vector<string> &get_samples();

    vector<string> infos() const;
    vector<string> formats() const;

    bool next();

    const Record& record() const;

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

    zstr::ifstream *mFile;
    uint64_t mStartOffset;
};
