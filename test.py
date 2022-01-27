
from vcfreader import VcfReader, Value

reader = VcfReader("/home/sacha/Dev/cutevariant/examples/snpeff3.vcf")

#reader = VcfReader("/home/sacha/Dev/test.vcf")

print(reader.info_keys())
count = 0

for record in reader:

	print("variant",record.pos(),record.format("AD"))

	count +=1
	


	




