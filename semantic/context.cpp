#include "context.hpp"

class Context {
private:
    map<string, Address> mlst;
    set<string> mgst;
    Context *mParent;
public:
Context::Context(set<string> gst, Context *parent) {
    mgst = gst;
    mParent = parent;
}
void Context::addSymbol(string sybl, Address addr) {
    mlst[]
}
    Address getSymbol(string sybl);
    Context *pop();
};

class ContextController {
    Context *top;
public:
    ContextController(set<string> gst);
    void pop();
    void push();
    void addSymbol(string sybl, Address addr);
    Address getSymbol(string sybl);
}

