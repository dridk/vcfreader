from vcfreader import VcfReader


reader = VcfReader("examples/test.snpeff.vcf.gz")


# print(reader.get_info("ANN").description)
# print(reader.get_format("GT").description)

# counter = 0
# print(reader.get_samples())
# while reader.next():
#     print(reader.record().chrom)
#     print(reader.record().pos)
#     print(reader.record().get_info("DP"))


for record in reader:
    print(record.chrom)
    print(record.pos)
    print(record.get_info("DP"))
    print(record.get_format(0, "GT"))
