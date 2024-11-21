#include <cstdio>
#include <iostream>

void print_number(int a[], int len) {
    for(int i=0;i<len;i++) {
        std::cout << a[i];
    }
    std::cout << std::endl;
};

void fill(int a[], int len) {
    for(int i=0;i<len;i++) {
        a[i] = i % 10;
    }
}

int main(int argc, char *argv[]) {
    const int SIZE = 20000;
    const int SSIZE = SIZE/2;
    int x[SSIZE];
    int y[SSIZE];
    int r[SIZE];
    int kpos;

    fill(x, SSIZE);
    fill(y, SSIZE);

    for(int i=0;i<SSIZE;i++) {
        for(int j=0;j<SSIZE;j++) {
            r[SIZE-i-j-1] += x[SSIZE-i-1]*y[SSIZE-j-1];
        }
        for(int k=0;k<SIZE-1;k++) {
            kpos = SIZE-k-1;
            r[kpos-1] += r[kpos] / 10;
            r[kpos] = r[kpos] % 10; 
        }
    }

    std::cout << std::endl;
    std::cout << "x = "; 
    print_number(x, SSIZE);
    std::cout << "y = "; 
    print_number(y, SSIZE);
    std::cout << "r = "; 
    print_number(r, SIZE);

    return 0;
}
