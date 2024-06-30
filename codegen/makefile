all: myobj 

clean: ./*.o
	rm ./*.o

myobj: codegen.cpp
	g++ -c *.cpp
	cp ./*.o ../product/obj

