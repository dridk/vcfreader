#include <QCoreApplication>
#include <QDebug>
#include "vcfreader.h"
int main(int argc, char *argv[])
{

    VcfReader reader("../examples/test.vep.vcf");


    for (auto i  : reader.get_samples())
        cout<<"ici"<<i<<endl;

    return 0;
}
