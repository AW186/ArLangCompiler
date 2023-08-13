#include "../syntax.hpp"
#include <sstream>

using namespace std;

LineSyntax::LineSyntax(AbstractLineContentSyntax *data) {
    this->line = data;
}

int LineSyntax::getType() {
    return SYN_LINE;
}
    
string LineSyntax::generateASM(ContextController *ctx) {
    cout << "line gen" << endl;
    this->print();
    return this->line->generateASM(ctx);
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