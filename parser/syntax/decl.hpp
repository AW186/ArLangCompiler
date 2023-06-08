#ifndef DECL_HPP
#define DECL_HPP

#include "abstractSyntax.hpp"

class DeclSyntax: public AbstractSyntax {
    string mId;
    string mType;
public:
    DeclSyntax(string type, string id);
    int getType() override;
};

#endif