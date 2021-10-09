//
// Created by Kacper Marczewski on 09/10/2021.
//
// Conversion between roman to arabic and arabic to roman numerals
//
//

#include<stdio.h>
#include <cstring>

const int CODE[] = {73, 86, 88, 76, 67, 68, 77};
const int VAL[] = {1, 5, 10, 50, 100, 500, 1000};
const int LEN = sizeof(CODE) / sizeof(int);

int roman_to_arabic(const char *r);

int get_val(char c);

int main(int argc, char *argv[]) {
    int result = roman_to_arabic("XLIV");
    printf("result = %d", result);
    return 0;
}

int roman_to_arabic(const char *r) {
    int len = strlen(r);
    int acc = 0;
    int next, val;
    for (int i = 0; i < len; i++) {
        next = (i + 1 == len) ? 0 : get_val(r[i + 1]);
        val = get_val(r[i]);
        if (val < next)
            acc -= val;
        else
            acc += val;
    }
    return acc;
}

int get_val(char c) {
    for (int i = 0; i < LEN; i++) {
        if (CODE[i] == c)
            return VAL[i];
    }
    return -1;
}
