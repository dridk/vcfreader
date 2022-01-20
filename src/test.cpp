#include "test.h"

#include <QObject>

#include "src/value.h"
#include "src/record.h"

void Test::initTestCase()
{

    std::setlocale(LC_ALL, "en_US.UTF-8");


}

void Test::test_value()
{


    QVERIFY(Value("324").toInt() == 324);
    QVERIFY(Value("-324").toInt() == -324);
    QVERIFY(Value("1").toBool() == true);
    QVERIFY(Value("0").toBool() == false);
    QVERIFY(Value("3.1").toDouble() == 3.1);
    QVERIFY(Value("3,4").toDouble() == 3.4);
    QVERIFY(Value("sacha").toString() == "sacha");



}

void Test::test_record()
{

    Record rec = Record::from_line(R"(
11/t125010/t./tT/tA/t./tPASS/tAC=1;AF=0.250;AN=4;BaseQRankSum=-3.111;
ClippingRankSum=-3.369;DP=94;ECNT=1;FS=2.107;HCNT=1;MQRankSum=-3.369;
NLOD=9.06;RAW_MQ=335641.00;ReadPosRankSum=-3.003;SOR=1.590;
TLOD=4.78/t
GT:AD:AF:F1R2:F2R1:DP:FOXOG:FT:QSS/t
0/0:40,1:0.024:19,0:21,1:41:1.00:.:1314,28/t
0/1:38,3:0.073:21,0:17,3:41:1.00:fake_genotype_filter:1180,81)");
    QVERIFY(rec.chrom() == "chr1");

}



QTEST_MAIN(Test)
