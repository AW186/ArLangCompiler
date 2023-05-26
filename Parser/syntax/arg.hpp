#ifndef ARG_HPP
#define ARG_HPP

#include "abstractSyntax.hpp"
#include <iostream>

using namespace std;

class Args: public AbstractSyntax {
private:
    string mType;
    string mId;
    Args *mNext;
public:
    Args(string type, string id, Args *next);
    int getType() override;
};

#endif