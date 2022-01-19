#include <QCoreApplication>
#include <QDebug>
#include <boost/algorithm/string.hpp>
#include "vcfreader.h"
int main(int argc, char *argv[])
{


    string test = "sacha le chat";

    vector<string> items;
    boost::split(items, test, boost::is_any_of(" "));

    for (auto i: items)
        cout<<"SPLIT: "<<i<<endl;

//    VcfReader reader("../examples/test.vep.vcf");


//    for (auto i  : reader.get_samples())
//        cout<<"ici"<<i<<endl;

    return 0;
}
