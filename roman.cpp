//
// Created by Kacper Marczewski on 09/10/2021.
//
// Conversion between roman to arabic and arabic to roman numerals
//
//

#include<stdio.h>
#include <cstring>

const int LEN = 7;
const int CODE[] = {73, 86, 88, 76, 67, 68, 77};
const int VAL[] = {1, 5, 10, 50, 100, 500, 1000};

int roman_to_arabic(const char *r);

int get_val(char c);

int main(int argc, char *argv[]) {
    roman_to_arabic("IVXLCDM");
    return 0;
}

int roman_to_arabic(const char *r) {
    int len = strlen(r);
    for (int i = 0; i < len; i++) {
        printf("%c %d\n", r[i], get_val(r[i]));
    }
    return 0;
}

int get_val(char c) {
    for (int i = 0; i < LEN; i++) {
        if (CODE[i] == c)
            return VAL[i];
    }
}
