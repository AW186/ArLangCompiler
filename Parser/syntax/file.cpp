#include "file.hpp"

FileSyntax::FileSyntax(ProgramSyntax *program) {
    this->mProgram = program;
}

int FileSyntax::getType() {
    return SYN_FILE;
}