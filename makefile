all: allobj

prelink: 
	# g++ -o acc product/obj/*.o

finallink:
	g++ -g acc.o `llvm-config --cxxflags --ldflags --system-libs --libs core` -o acc

allobj: main.cpp parserobj lexerobj codegenobj
	g++ -g -c *.cpp
	cp *.o product/obj
	g++ -g product/obj/*.o `llvm-config --cxxflags --ldflags --system-libs --libs core` -o acc
	rm ./*.o

parserobj: ./parser
	cd parser && $(MAKE)

codegenobj: ./semantic
	cd codegen && $(MAKE)

lexerobj: ./lexer
	cd lexer && $(MAKE)

clean:
	rm ./product/obj/*
