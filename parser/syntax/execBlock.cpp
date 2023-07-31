#include "../syntax.hpp"

LineSyntax::LineSyntax(AbstractLineContentSyntax *data) {
    this->line = data;
}

int LineSyntax::getType() {
    return SYN_LINE;
}

LinesSyntax::LinesSyntax(LineSyntax *line, LinesSyntax *next) {
    this->mLine = line;
    this->mNext = next;
}

int LinesSyntax::getType() {
    return SYN_LINES;
}

ExecBlockSyntax::ExecBlockSyntax(LinesSyntax *lines) {
    this->mLines = lines;
}

int ExecBlockSyntax::getType() {
    return SYN_BLOCK;
}