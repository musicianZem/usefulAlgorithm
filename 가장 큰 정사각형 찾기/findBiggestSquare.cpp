#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int origin[2000][2000];
int cache[2000][2000]; // init 0

// O(N*M, N^2)
int getLargestSquareSize(int arrSize, int threshold) {
    int result = 0;

    memset(cache, 0, sizeof(cache));
    for(int i=0; i<arrSize; i++) {
        cache[i][0] = origin[i][0] > threshold; // 0 or 1
        cache[0][i] = origin[0][i] > threshold; // 0 or 1
    } // end of init cache.

    for(int i=1; i<arrSize; i++) {
        for(int j=1; j<arrSize; j++) {
            cache[i][j] = min(cache[i-1][j-1], min(cache[i][j-1], cache[i-1][j]));
            if( origin[i][j] > threshold )
                cache[i][j] ++;
            result = max(cache[i][j], result);
        }
    }

    return result;
}

int main() {
    srand((unsigned int) time (NULL));
    for(int i=0; i<2000; i++) {
        for(int j=0; j<2000; j++) {
            origin[i][j] = rand()%100;
        }
    } // end of make random

    for(int i=10; i<100; i+=10) {
        cout << i << " : " << getLargestSquareSize(2000, i) << endl;
    }

    return 0;
}
