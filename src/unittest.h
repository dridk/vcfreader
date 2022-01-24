#include "gtest/gtest.h"
#include "value.h"
#include "utils.h"
#include "vcfreader.h"
#include <iostream>
namespace
{
// The fixture for testing class Foo.
class ValueTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    ValueTest()
    {
        std::setlocale(LC_ALL, "en_US.UTF-8");

    }
    virtual ~ValueTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that Foo does Xyz.
TEST_F(ValueTest, ToInt)
{
    ASSERT_EQ(Value("324").toInt() , 324);
    ASSERT_EQ(Value("-324").toInt() , -324);
    ASSERT_EQ(Value("1").toBool() , true);
    ASSERT_EQ(Value("0").toBool() , false);
    ASSERT_EQ(Value("3.1").toDouble() , 3.1);
    ASSERT_EQ(Value("3,4").toDouble() , 3.4);
    ASSERT_EQ(Value("sacha").toString() , "sacha") << "marche pas";
}



// The fixture for testing class Foo.
class VcfReaderTest : public ::testing::Test
{
protected:

    const std::string filename = "/home/sacha/Dev/vcfreader/examples/test.snpeff.vcf.gz";


};

// Tests that Foo does Xyz.
TEST_F(VcfReaderTest, Test_Get_Samples)
{
    ASSERT_TRUE(utils::file_exists((filename)));

    std::vector<std::string> expected = {"NORMAL","TUMOR"};
    auto reader = VcfReader(filename);
    ASSERT_TRUE(reader.samples() == expected);


}

TEST_F(VcfReaderTest, Test_meta)
{
    ASSERT_TRUE(utils::file_exists((filename)));

    auto reader = VcfReader(filename);

    ASSERT_TRUE(utils::contains(reader.info_keys(), std::string("AF")));
    ASSERT_TRUE(utils::contains(reader.info_keys(), std::string("DP")));
    ASSERT_TRUE(utils::contains(reader.format_keys(), std::string("GT")));

    ASSERT_TRUE(reader.info("AF").type == Value::Double);

}

TEST_F(VcfReaderTest, Test_read_first_line)
{
    ASSERT_TRUE(utils::file_exists((filename)));

    auto reader = VcfReader(filename);

    Record record;
    while (reader.next())
    {
        record = reader.record();
        break;
    }

// GT:AD:AF:F1R2:F2R1:DP:FOXOG:QSS 0/0:64,0:0.00:24,0:40,0:64:NaN:2342,0  0/1:48,4:0.077:19,4:29,0:52:1.00:1726,93

    ASSERT_TRUE(record.chrom() == "11");
    ASSERT_TRUE(record.pos() == 10000 ) << record.pos();
    ASSERT_TRUE(record.id() == ".");
    ASSERT_TRUE(record.ref() == "G");
    ASSERT_TRUE(record.alt() == "T");
    ASSERT_TRUE(record.qual() == ".");
    ASSERT_TRUE(record.filter() == "PASS");

//// Test INFO
   ASSERT_TRUE(record.info("AC").toInt() == 1);
   ASSERT_TRUE(record.info("AF").toDouble() == 0.250);
   ASSERT_TRUE(record.info("BaseQRankSum").toDouble() == -3.321);
   ASSERT_TRUE(record.info("DB").toBool() == false);

// TEST FORMAT

  ASSERT_TRUE(record.format("GT", 0).toString() == "0/0");
  ASSERT_TRUE(record.format("GT", 1).toString() == "0/1");


}










}
