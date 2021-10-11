//
// Created by Kacper Marczewski on 09/10/2021.
//
// Conversion between roman to arabic and arabic to roman numerals
//
//

#include <cstdio>
#include <cstring>

const int CODE[] = {77, 68, 67, 76, 88, 86, 73};
const int VAL[] = {1000, 500, 100, 50, 10, 5, 1};
const int LEN = sizeof(CODE) / sizeof(int);

int roman_to_arabic(const char *r);

void arabic_to_roman(int v, char *roman);

int get_val(char c);

int min(int a, int b);

int code_to_val(int code);

int main(int argc, char *argv[]) {
    int arabic = roman_to_arabic("XLIV");
    char roman[20];
    printf("arabic = %d\n", arabic);
    arabic_to_roman(arabic, roman);
    printf("roman = %s\n", roman);
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

void arabic_to_roman(int v, char *roman) {
    int num = min(3999, v);
    int i;
    int len = (int) strlen(roman);
    int r_len = 0;
    for (int k = 0; k < len; k = k + 2) {
        i = num / VAL[k];
        if (i > 3) {
            if (i == 9) {
                roman[r_len] = VAL[k];
                r_len++;
                roman[r_len] = VAL[k - 2];
                r_len++;
            } else {
                if (i == 4) {
                    roman[r_len] = VAL[k];
                    r_len++;
                }
                roman[r_len] = VAL[k - 1];
                r_len++;
                for (int j = 5; j < i; j++) {
                    roman[r_len] = VAL[k];
                    r_len++;
                }
            }
        } else {
            for (int j = 0; j < i; j++) {
                roman[r_len] = VAL[k];
                r_len++;
            }
        }
        num -= i * VAL[k];
    }
    roman[r_len] = 0;
}

int min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

int get_val(char c) {
    for (int i = 0; i < LEN; i++) {
        if (CODE[i] == c)
            return VAL[i];
    }
    return -1;
}

