//
// Created by Kacper Marczewski on 10/09/2021.
//
// BlackJack simulation
//
//

#include <cstdio>
#include <cmath>
#include <random>

const long COUNT = 1000000;

int main(int argc, char *argv[]) {
    printf("trying... %ld\n", COUNT);
    long inside = 0;
    double x, y;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> r(-1.0, 1.0);
    for (int i = 0; i < COUNT; i++) {
        x = r(mt);
        y = r(mt);
        if (sqrt(x * x + y * y) < 1.0)
            inside++;
    }
    double pi = 4.0 * (double(inside)) / (double(COUNT));
    printf("pi estimated = %.6f\n", pi);
    printf("error = %.6f\n", abs(pi - M_PI));
    return 0;
}
