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

int main(int argc, char *argv[]) {
    int inside = 0;
    int count = 100000;
    float x,y;
    for(int i=0;i<count;i++) {
        x = get_float(mt);
        y = get_float(mt);
        if((x*x + y*y) < 1.0)
            inside++;
    }
    float pi = 4.0 * (((float) inside )/ ((float) count));

    printf("pi = %f\n", pi);
}