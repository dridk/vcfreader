#include <string>
#include <map>
#include <vector>
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
		uint64_t pos;
		string id;
		string ref;
		string alt;
		uint64_t qual;
		string filter;


	};



	class VcfReader {

	public:
		VcfReader(const string& filename);

		const Header& get_info(const string& key);
		const Header& get_format(const string& key);


	protected:
		void readHeader();




	private:
		Record mCurrent;
		string mFilename;
		map<string, Header> mFormats;
		map<string, Header> mInfos;
		map<string, Header> mFilter;

	};