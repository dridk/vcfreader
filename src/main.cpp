#include "unittest.h"

int main(int argc, char **argv) 
{

//    auto reader = VcfReader("/home/sacha/Dev/cyvcf2/cyvcf2/tests/test.mnp.vcf");

//    while (reader.next())
//    {
//        cout<<reader.record().format("GL").toList().size()<<endl;
//    }

//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

    std::unordered_map<std::string, int> test = {{"salut",34}, {"boby",34}};

    for (auto i : utils::get_keys(test))
        cout<<i<<endl;



}
