all: obj myobj clean

obj: ./syntax/* ./lalrgen/* ../lexer/*
	cd syntax && $(MAKE)
	cd lalrgen && $(MAKE)
	cd ../lexer && $(MAKE)

parser: allobj
	g++ *.o

clean: ./*.o
	rm ./*.o

myobj: ./*.cpp ./*.hpp ./syntax/*.hpp ./lalrgen/*.hpp ../lexer/*.hpp
	g++ -c *.cpp
	cp ./*.o ../product/obj

