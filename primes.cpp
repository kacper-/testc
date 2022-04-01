//
// Created by Kacper Marczewski on 01/04/2022.
//
// Searching for primes
//
//

#include <cstdio>
#include <cmath>

int main(int argc, char *argv[]) {
    printf("Primes from 1000100 to 1000200\n");

    for(int i=1000100;i<1000200;i++)
    {
        bool prime = true;
        int sqroot = sqrt(i);
        for(int j=2;i<sqroot;j++)
        {
            if(i % j == 0)
            {
                prime = false;
                break;
            }
        }
        if(prime)
            printf("%d\n", i);
    }

    return 0;
}