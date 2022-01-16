#include <string>
#include <map>
#include <vector>
#include <zstr.hpp>
#include <sstream>  
using namespace std;
/*

class Value {
public:

	enum Type {

		Int = 0,
		Float = 1,
		Str = 2,
		Bool = 3,
		List = 4	
	};
*/


	struct Header {

		string HeaderType;
		string id;
		string number;
		string type;
		string description;
	};

	struct Record {

		string chrom;
		int pos;
		string id;
		string ref;
		string alt;
		int qual;
		string filter;


	};



	class VcfReader {

	public:
		VcfReader(const string& filename);

		const Header& get_info(const string& key);
		const Header& get_format(const string& key);

		bool next();

		const Record& record() const;


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

		zstr::ifstream * mFile;


		uint64_t mStartOffset;

	};