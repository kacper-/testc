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
    printf("Primes from 1000001000 to 1000002000\n");

    for(long i=1000001000;i<1000002000;i++)
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
            std::cout << i << std::endl;
    }

    return 0;
}