all: parser

obj: ./syntax/* ./lalrgen/* ../lexer/*
	cd syntax && $(MAKE)
	cd lalrgen && $(MAKE)
	cd ../lexer && $(MAKE)

allobj: obj myobj
	cp ../product/obj/*.o ./

parser: allobj
	g++ *.o

clean: ./*.o
	rm ./*.o

myobj: ./*.cpp ./*.hpp ./syntax/*.hpp ./lalrgen/*.hpp ../lexer/*.hpp
	g++ -c *.cpp

product: myobj
	cp ./*.o ../product/obj
