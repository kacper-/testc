#include<stdio.h>

int main(int argc, char *argv[]) {

int x;
int y{};

printf("x=%d y=%d", x, y);

int a=9;
int b=4;
int c=7;
int d=1;
int e=3;

while((a=1)==1 && (b=2)==3 && (c=3)==3 || (d=4)==4 || (e=5)==7) {
    printf("a=%d b=%d c=%d d=%d e=%d\n", a, b, c, d, e);
    break;
}

}