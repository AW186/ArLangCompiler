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
    
string LineSyntax::generateASM(ContextController *ctx) {
    string res = this->line->generateASM(ctx);
    return res;
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

string LinesSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    cout << "lines generate asm" << endl;
    ss << this->mLine->generateASM(ctx) << endl;
    if (this->mNext) ss << this->mNext->generateASM(ctx) << endl;
    return ss.str();
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

string ExecBlockSyntax::generateASM(ContextController *ctx) {
    ctx->push();
    cout << "block generate asm" << endl;
    string res = this->mLines->generateASM(ctx);
    ctx->pop();
    return res;
}

void ExecBlockSyntax::print() {
    cout << "Block {" << endl;
    this->mLines->print();
    cout << "}";
}

void ExecBlockSyntax::fixLiteral(vector<string> & lines) {
    cout << "fixing block" << endl;
    this->mLines->fixLiteral(lines);
}

void LinesSyntax::fixLiteral(vector<string> & lines) {
    cout << "fixing lines" << endl;
    this->mLine->fixLiteral(lines);
    if (this->mNext) this->mNext->fixLiteral(lines);
}

void LineSyntax::fixLiteral(vector<string> & lines) {
    cout << "fixing line" << endl;
    this->line->fixLiteral(lines);
}




