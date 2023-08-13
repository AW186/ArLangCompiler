#include "file.hpp"

FileSyntax::FileSyntax(ProgramSyntax *program) {
    this->mProgram = program;
}

int FileSyntax::getType() {
    return SYN_FILE;
}

string FileSyntax::generateASM(ContextController *ctx) {
    return this->mProgram->generateASM(ctx);
}

void FileSyntax::print() {
    cout << "FILE BEGIN" << endl;
    this->mProgram->print();
    cout << "FILE END" << endl;
}