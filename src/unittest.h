#include "gtest/gtest.h"
#include "value.h"
#include "utils.h"

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
class VcfReaderTest : public ::testing::TestWithParam<std::string>
{
protected:



};

// Tests that Foo does Xyz.
TEST_P(VcfReaderTest, Test_Value)
{
    auto test = GetParam();

    ASSERT_FALSE(utils::file_exists(test));
}



INSTANTIATE_TEST_CASE_P(
        VcfReaderTestFixture,
        VcfReaderTest,
        ::testing::Values(
                "sacha","sacdsg"
        ));











}
