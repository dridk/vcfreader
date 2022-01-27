#include "unittest.h"
#include <fstream>


int main(int argc, char **argv) 
{

    const char* filename = "/home/sacha/Dev/test3.vcf.gz";
    auto reader = VcfReader(filename);

    while (reader.next())
    {
        double progress = double(reader.read_bytes()) / double(reader.total_bytes());

        cout<<progress<<endl;
    }



//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

//    std::unordered_map<std::string, int> test = {{"salut",34}, {"boby",34}};

//    for (auto i : utils::get_keys(test))
//        cout<<i<<endl;



}
