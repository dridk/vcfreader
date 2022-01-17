#include <string>
#include <map>
#include <vector>
#include <zstr.hpp>
#include <sstream>

using namespace std;
/*

class Value {
public:

*/

enum Type: unsigned int;

struct Value;
struct Header;
struct Record;

enum Type: unsigned int
{

	Int = 0,
	Float = 1,
	Str = 2,
	Bool = 3,
	List = 4
};

struct Header
{

	string HeaderType;
	string id;
	string number;
	string type;
	string description;
};

struct Record
{

	string chrom;
	unsigned long pos;
	string id;
	string ref;
	string alt;
	string qual;
	string filter;
	map<string,Value> infos;

	const Value& get_info(const string &key) const;

	// vector<Value> formats;
};

//Handy way to define any python key,value pair type
struct Value
{
	string type;
	//DP=15:AF=0.3:
	string key;
	string value;
};

class VcfReader
{

public:
	VcfReader(const string &filename);

	const Header &get_info(const string &key);
	const Header &get_format(const string &key);

	bool next();

	const Record &record() const;

protected:
	void readHeader();
	void readRecord();

private:
	string mCurrentLine;
	Record mCurrentRecord;
	string mFilename;
	map<string, Header> mFormats;
	map<string, Header> mInfos;
	map<string, Header> mFilter;

	zstr::ifstream *mFile;

	uint64_t mStartOffset;
};