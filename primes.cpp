//
// Created by Kacper Marczewski on 01/04/2022.
//
// Searching for primes
//
//

#include <cstdio>
#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
    printf("Primes from 1010000000 to 1020000000\n");

    int count = 0;

    for(long i=1010000000;i<1020000000;i++)
    {
        int prime = 1;
        long sqroot = sqrt(i);
        for(long j=2;j<sqroot;j++)
        {
            if(i % j == 0)
            {
                prime = 0;
                break;
            }
        }
        if(prime)
            count++;
    }

    std::cout << count << std::endl;

    return 0;
}