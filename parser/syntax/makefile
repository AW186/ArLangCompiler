all: product

obj: ./*.cpp ./*.hpp
	g++ -c *.cpp

clean: ./*.o
	rm *.o

product: obj
	cp ./*.o ../../product/obj
	make clean