#ifndef FILE_HPP
#define FILE_HPP

#include "../syntax.hpp"

class FileSyntax: public AbstractSyntax {
private:
    ProgramSyntax *mProgram;
public:
    int getType() override;
    FileSyntax(ProgramSyntax *program);
    string generateASM(ContextController *ctx) override;
    void print() override;
    void fixLiteral(vector<string> & lines) override;
    void declaration(vector<string> & lines) override;
};

#endif
