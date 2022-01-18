
#include <iostream>
#include "vcfreader.h"
using namespace std;


int main()
{

    VcfReader reader("../examples/test.snpeff.vcf.gz");


     cout<<reader.get_samples()[0]<<endl;



	return 0;
}
