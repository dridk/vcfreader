#include "unittest.h"

int main(int argc, char **argv) 
{

    auto reader = VcfReader("/home/sacha/Dev/test.vcf");

    while (reader.next())
    {
        cout<<reader.record().info("SRF").to_int()<<endl;
    }

//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

//    std::unordered_map<std::string, int> test = {{"salut",34}, {"boby",34}};

//    for (auto i : utils::get_keys(test))
//        cout<<i<<endl;



}
