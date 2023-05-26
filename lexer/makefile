all: test

test: main.o rule.o lexer.o
	g++ -o test main.o rule.o lexer.o

main.o: main.cpp lexer.hpp reader.hpp rule.hpp
	g++ -c main.cpp

rule.o: rule.cpp lexer.hpp reader.hpp rule.hpp
	g++ -c rule.cpp

lexer.o: lexer.cpp lexer.hpp reader.hpp rule.hpp
	g++ -c lexer.cpp

clean:
	rm *.o
	rm test
	