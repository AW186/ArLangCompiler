#ifndef PARSER_HPP
#define PARSER_HPP

#include "lalrgen/lrgen.hpp"
#include "../lexerlib.hpp"
#include "syntax.hpp"


AbstractSyntax *makeSyntaxTree(Lexer *lex, vector<vector<action>> lrtable, map<int, int> mapping);

#endif