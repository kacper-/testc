#include <iostream>

// by value
void add_two1(int arg) {
    arg = arg + 2;
}

// by pointer
void add_two2(int * arg) {
    *arg = *arg + 2;
}

// by reference
void add_two3(int & arg) {
    arg = arg + 2;
}


int main(int argc, char *argv[]) {
    int first = 1;
    int second = 1;
    int third = 1;

    add_two1(first);
    add_two2(&second);
    add_two3(third);

    std::cout << "First  : " << first << std::endl;
    std::cout << "Second : " << second << std::endl;
    std::cout << "Third  : " << third << std::endl;

    return 0;
}