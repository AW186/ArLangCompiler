#ifndef FILE_HPP
#define FILE_HPP

#include "../syntax.hpp"

class FileSyntax: public AbstractSyntax {
private:
    ProgramSyntax *mProgram;
public:
    int getType() override;
    FileSyntax(ProgramSyntax *program);
};

#endif