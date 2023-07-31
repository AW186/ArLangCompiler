#ifndef DECL_HPP
#define DECL_HPP

#include "abstractSyntax.hpp"
#include "execBlock.hpp"

class DeclSyntax: public AbstractLineContentSyntax {
    string mId;
    string mType;
public:
    DeclSyntax(string type, string id);
    int getType() override;
};

#endif