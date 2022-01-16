

from vcfreader import VcfReader 



reader = VcfReader("examples/test.snpeff.vcf.gz")


print(reader.get_info("ANN").description)
print(reader.get_format("GT").description)

