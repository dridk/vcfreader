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

// HELPER ... 

bool is_digit(const string& str);



enum Type: unsigned int;

struct Value;
struct Header;
struct Record;
class VcfReader;

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
	uint dim;
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
	
	vector< map<string,Value> >formats;

	const Value& get_info(const string &key) const;
	const Value& get_format(int index, const string& key) const;

	// vector<Value> formats;
};

//Handy way to define any python key,value pair type
struct Value
{
	uint dim; 
	string type;
	string key;
	string value;
};

class VcfReader
{

public:
	VcfReader(const string &filename);

	const Header &get_info(const string &key);
	const Header &get_format(const string &key);
	const vector<string> &get_samples();

	bool next();

	const Record &record() const;

	VcfReader * __iter__();
	const Record& __next__();



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
	vector<string> mSamples;

	zstr::ifstream *mFile;

	uint64_t mStartOffset;
};