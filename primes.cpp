//
// Created by Kacper Marczewski on 01/04/2022.
//
// Searching for primes
//
//

#include <cstdio>
#include <iostream>
#include <cmath>

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char *argv[]) {
    const int FROM = 1000000000;
    const int TO = 1000100000;
    int limit = sqrt(TO);
    int a[TO-FROM]; 

    uint64_t start = timeSinceEpochMillisec();

    int n,i;

    for(n=FROM;n<TO;n++) {
        for(i=2;i<limit;i++) {
            if( n % i == 0) {
                a[n - FROM] = 1;
                break;
            }
        }
    }

    uint64_t elapsed = timeSinceEpochMillisec() - start;

    

    for(i=0;i<TO-FROM;i++) {
        if(a[i] != 0)
            std::cout << a[i] << "\n";
    }

    std::cout << elapsed << std::endl;

    return 0;
}
