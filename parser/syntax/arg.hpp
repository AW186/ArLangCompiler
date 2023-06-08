#ifndef ARG_HPP
#define ARG_HPP

#include "abstractSyntax.hpp"
#include <iostream>

using namespace std;

class ArgsSyntax: public AbstractSyntax {
private:
    string mType;
    string mId;
    ArgsSyntax *mNext;
public:
    ArgsSyntax(string type, string id, ArgsSyntax *next);
    int getType() override;
};

#endif