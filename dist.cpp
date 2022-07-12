//
// Created by Kacper Marczewski on 09/10/2021.
//
// Conversion between roman to arabic and arabic to roman numerals
//
//

#include <cstdio>
#include <cstring>
#include <random>
#include <unistd.h>

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> get_float(0, 1);

const int ITER = 10000000;

int main(int argc, char *argv[]) {
    int t[5];
    for(int i=0;i<5;i++)
        t[i]=0;
    for(int i=0;i<ITER;i++)
        t[(int)(5 * get_float(mt))]++;
    for(int i=0;i<5;i++) {
        int diff = abs((ITER/5) - t[i]);
        printf("%d = %d diff = %f\n", i + 1, t[i], ((float)diff) / ((float) ITER/5));
    }
}
