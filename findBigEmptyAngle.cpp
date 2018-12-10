#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

pair<int, int> findLargestAngle(int *arr, int arrSize, int threshold) {
    int firstOverflow = -1;

    int glob_maxSize = 0, glob_maxStart = 0;
    int temp_maxSize = 0, temp_maxStart = 0;

    for(int i=0; i<arrSize; i++) {
        if( arr[i] < threshold ) {
            if( firstOverflow == -1 ) {
                firstOverflow = i;
            }

            if( glob_maxSize < temp_maxSize ) {
                glob_maxSize  = temp_maxSize;
                glob_maxStart = temp_maxStart;
            }

            temp_maxSize = 0;
            temp_maxStart = i+1;
        } else {
            temp_maxSize++;
        }
    }

    if( firstOverflow == -1 ) {
        glob_maxSize = temp_maxSize;
        glob_maxStart = 0;
    } else if( glob_maxSize < temp_maxSize ) {
        glob_maxSize  = temp_maxSize;
        glob_maxStart = temp_maxStart;
    }

    return make_pair( glob_maxSize, glob_maxStart );
}

void initRandomSeed() {
    srand((unsigned int) time (NULL));
}

void makeArrayRandom(int *arr, int arrSize) {
    for(int i=0; i<arrSize; i++) {
        arr[i] = rand()%255;
    }
}

int main() {
    initRandomSeed();

    int arr[36];
    makeArrayRandom(arr, 36);
    pair<int, int> checker;

    for(int i=0; i<36; i++) {
        cout << "arr["<<i<<"] = " << arr[i] << endl;
    }
    for(int i=10; i<100; i+=10) {
        checker = findLargestAngle(arr, 36, i);
        cout << "threshold [" << i << "] max Size = " << checker.first << ", max Start = " << checker.second << endl;
    }
}
