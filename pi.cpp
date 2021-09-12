//
// Created by Kacper Marczewski on 10/09/2021.
//
// PI estimated with Monte Carlo method
//
//

#include <cstdio>
#include <cmath>
#include <random>

const long S_1M = 1000000;
const long S_10M = 10000000;
const int REP = 10;

double calc_pi(long s);

int main(int argc, char *argv[]) {
    printf("trying... %d\n", REP);
    double pi, error;
    double avg_error = 0.0;
    double avg_pi = 0.0;
    for (int i = 0; i < REP; i++) {
        pi = calc_pi(S_1M);
        error = abs(pi - M_PI);
        printf("\tseq\t%d\t%.6f\t%.6f\n", i + 1, pi, error);
        avg_pi += pi;
        avg_error += error;
    }
    printf("avg pi %.6f +/- %.6f\n", avg_pi / REP, error / REP);
    return 0;
}

double calc_pi(long s) {
    long inside = 0;
    double x, y;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> r(-1.0, 1.0);
    for (int i = 0; i < s; i++) {
        x = r(mt);
        y = r(mt);
        if (sqrt(x * x + y * y) < 1.0)
            inside++;
    }
    return 4.0 * (double(inside)) / (double(s));
}