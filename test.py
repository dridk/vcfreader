from vcfreader import VcfReader


reader = VcfReader("../examples/test.vep.vcf")


print(reader.get_samples())


# print(reader.get_info("ANN").description)
# print(reader.get_format("GT").description)

# counter = 0
# print(reader.get_samples())
# while reader.next():
#     print(reader.record().chrom)
#     print(reader.record().pos)
#     print(reader.record().get_info("DP"))


# for record in reader:
#     print(record.get_format(0,"GT"))

#     break

