int main(int argc) {
    int x;
    x = (100 + 2);
    if 1 {
        syscall(1, 1, "hello", 5);
    }
    int i;
    for i = 0; (i < 10); i = (i + 1); {
        syscall(1, 1, "looping", 7);
    }
}