all: allobj


allobj: main.cpp parserobj semanticobj lexerobj
	g++ -c *.cpp
	cp *.o product/obj
	g++ -o acc product/obj/*.o
	rm ./*.o

parserobj: ./parser
	cd parser && $(MAKE)

semanticobj: ./semantic
	cd semantic && $(MAKE)

lexerobj: ./lexer
	cd lexer && $(MAKE)