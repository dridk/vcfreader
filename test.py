
from vcfreader import VcfReader, Value

reader = VcfReader("examples/test.snpeff.vcf.gz")

for record in reader:

	print(record.chrom(), record.pos(),record.format("GT"))

	


	




