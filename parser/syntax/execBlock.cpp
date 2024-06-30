#include "../syntax.hpp"
#include "execBlock.hpp"
#include <sstream>

using namespace std;

LineSyntax::LineSyntax(AbstractLineContentSyntax *data) {
    this->line = data;
}

int LineSyntax::getType() {
    return SYN_LINE;
}
    

void LineSyntax::print() {
    this->line->print();
    cout << endl;
}

LinesSyntax::LinesSyntax(LineSyntax *line, LinesSyntax *next) {
    this->mLine = line;
    this->mNext = next;
}

int LinesSyntax::getType() {
    return SYN_LINES;
}

void LinesSyntax::print() {
    this->mLine->print();
    if (this->mNext) this->mNext->print();
}

ExecBlockSyntax::ExecBlockSyntax(LinesSyntax *lines) {
    this->mLines = lines;
}

int ExecBlockSyntax::getType() {
    return SYN_BLOCK;
}

void ExecBlockSyntax::print() {
    cout << "Block {" << endl;
    this->mLines->print();
    cout << "}";
}

