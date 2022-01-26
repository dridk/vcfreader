
from vcfreader import VcfReader, Value

#reader = VcfReader("/home/sacha/Dev/cutevariant/examples/snpeff3.vcf")

reader = VcfReader("/home/sacha/Dev/test.vcf")

print(reader.info_keys())
count = 0

for record in reader:

	print("CCCCCC",count)
	for key in record.info_keys():
		print(key)
		
		print("variant",record.info(key))

	count +=1
	


	




