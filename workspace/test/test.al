int main(int argc) {
    int x;
    x = argc;
    x = (x + 2);
    if argc {
        x = (x + 100);
    };
    return x;
}

int pow(int base, int exp) {
    if exp {
        return pow(base, (exp - 1));
    } else {
        return 1;
    };
}

int pow2(int base, int exp) {
    int res;
    res = 1;
    int i;
    for i = exp; i; i = (i - 1); {
        res = (res * base);
    }
    return res;
}

