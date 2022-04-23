#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
    int a;
    int b=4;
    printf("%d\n", a=3);

    int& aref = a;
    printf("%d\n", aref);
    aref = b;
    printf("%d\n", aref);

    std::cout << &aref << std::endl << &a;
    std::cout << aref << std::endl;
    return 0;
}