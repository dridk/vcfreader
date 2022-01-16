

from distutils.core import setup, Extension
from glob import glob 



ZLIB_SRC =['zlib/contrib/minizip/zip.c', 'zlib/contrib/minizip/unzip.c', 'zlib/contrib/minizip/ioapi.c',
'zlib/adler32.c', 'zlib/compress.c', 'zlib/crc32.c', 'zlib/deflate.c',
'zlib/infback.c', 'zlib/inffast.c', 'zlib/inflate.c',
'zlib/inftrees.c', 'zlib/trees.c', 'zlib/uncompr.c', 'zlib/zutil.c']

#SOURCE.append("zlib/contrib/minizip/iowin32.c")

vcfreader_module = Extension('_vcfreader',
	sources=["src/vcfreader.cpp",
	"src/vcfreader_wrap.cxx"] + ZLIB_SRC ,  
	
	include_dirs=['zstr','zlib','src'])



setup(
	name="vcfreader",
	version="0.1",
	author="Sacha Schutz",
	ext_modules = [vcfreader_module],
	package_dir={'': 'src'},
	packages = [''],
	)