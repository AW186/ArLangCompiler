#include "rule.hpp"
#include <map>
#include <vector>
#include <string.h>
#include <iostream>

#define ALPHA "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
#define REG "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890"
#define DIGIT "1234567890"

using namespace std;

int kind[MAXRULE] = {
    NOTEND,
    NOTEND,
    INTMED,
    NOTEND,
    INTMED,
    NOTEND,
    NOTEND,
    INTMED, 
    ID, 
    ID, 
    OPRAND, 
    NOTEND, 
    IGNORE, 
    OPRAND, 
    IGNORE
};

mask emptyMask() {
    mask res;
    bzero(&res, sizeof(res));
    return res;
}

mask fullMask() {
    mask res = emptyMask();
    res.mask[0]--;
    res.mask[1]--;
    res.mask[2]--;
    res.mask[3]--;
    return res;
}

mask getMask(string str) {
    mask res = emptyMask();
    for (int i = 0; i < str.size(); i++) {
        res.mask[MASKBLKID(str[i])] |= MASKDIGIT(str[i]);
        // printf("c: %d, id: %d, offset: %x\n", str[i], MASKBLKID(str[i]), MASKDIGIT(str[i]));

    }
    return res;
}

mask setMask(mask m, int index) {
    m.mask[MASKBLKID(index)] |= MASKDIGIT(index);
    return m;
}

mask notMask(string str) {
    mask res = fullMask();
    for (int i = 0; i < str.size(); i++) {
        res.mask[MASKBLKID(str.at(i))] -= MASKDIGIT(str.at(i));
    }
    return res;
}

void printMask(mask m) {
    cout << "mask: ";
    for (uint8_t i = 0; i < 255; i++) {
        int val = i;
        if (check(m, i)) cout << val << " ";
    }
    cout << "end" << endl;
}

void link(vector<State> &states, mask condition, int fromId, int toId);


void link(vector<State *> &states, mask condition, int fromId, int toId) {
    states[fromId] = new State(fromId, states[fromId], condition, toId);
}

bool check(mask m, uint8_t index) {
    return m.mask[MASKBLKID(index)] & MASKDIGIT(index);
}


vector<State *> makeArLangRule() {
    vector<State *> states(MAXRULE);
    for (int i = 0; i < MAXRULE; i++)
        states[i] = new State(i, NULL, emptyMask(), -1);
    const mask alpha = getMask(ALPHA);
    const mask reg = getMask(REG);
    const mask digit = getMask(DIGIT);
    const mask op = getMask("|&^!+-*(){}[];=");
    //number
    link(states, digit, 0, 2);
    link(states, digit, 2, 2);
    link(states, getMask("."), 2, 3);
    link(states, digit, 3, 4);
    link(states, digit, 4, 4);
    //string
    link(states, getMask("\""), 0, 5);
    link(states, reg, 5, 6);
    link(states, reg, 6, 6);
    link(states, getMask("\""), 6, 7);
    //id
    link(states, alpha, 0, 8);
    link(states, reg, 8, 9);
    link(states, reg, 9, 9);
    //comment
    link(states, getMask("/"), 0, 10);
    link(states, getMask("/"), 10, 11);
    link(states, notMask("\n\r"), 11, 11);
    //oprand
    link(states, op, 0, 13);
    //ignore
    link(states, setMask(getMask("\n\r"), 32), 0, 14);
    link(states, setMask(getMask("\n\r"), 32), 14, 14);
    
    return states;    
}