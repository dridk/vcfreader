

testreader: src/vcfreader.cpp src/main.cpp
	g++ -o $@ $^  -Isrc -Izstr -lz -std=c++11 ;
	./testreader

testpython: 
	swig -c++ -python src/vcfreader.i
	python setup.py install 
	python test.py