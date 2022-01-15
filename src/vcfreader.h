#include <string>
using namespace std;


class VcfReader {

public:
	VcfReader(const string& filename);
	bool next();

	int value() const;

	void test() const;

private:
	string mFilename;


};