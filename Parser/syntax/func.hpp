#ifndef FUNC_HPP
#define FUNC_HPP

#include "abstractSyntax.hpp"

class FuncSyntax: public AbstractSyntax {

public:
    FuncSyntax();
    int getType() override;
};

#endif