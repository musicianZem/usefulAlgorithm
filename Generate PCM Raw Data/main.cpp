#include <iostream>
#include <math.h>
#include <stdio.h>

int hz_list[12] =
{
    500,
    1000,
    2000,
    3000,
    4000,
    5000,
    6000,
    7000,
    8000,
    10000,
    15000,
    20000
};

using namespace std;
int main() {
    FILE *fout = fopen("test.pcm", "w");

    int SAMPLE_RATE = 44100;

    for(int testCount = 0; testCount < 12; testCount++) {
        for(long i=0; i<SAMPLE_RATE/2; i++) {
            // 16bit MAX 0x8000, times UNDER 1.0
            int sinus = (int)(0.8 * 0x8000 * sin (2 * M_PI * hz_list[testCount] * i / SAMPLE_RATE));

            fprintf(fout, "%c", sinus & 0xFF);
            fprintf(fout, "%c", (sinus >> 8) & 0xFF);
        }
    }

    fclose(fout);
}

