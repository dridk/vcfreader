

from vcfreader import VcfReader 



reader = VcfReader("examples/test.snpeff.vcf.gz")


print(reader.get_info("ANN").description)
print(reader.get_format("GT").description)

counter = 0
while reader.next():
	print(reader.record().chrom);
	print(reader.record().pos);




# for variant in reader:

# 	sql.import_variant(variant)

	# print(variant.chrom)
	# print(variant.pos)

	# print(variant.format["ANN"])











