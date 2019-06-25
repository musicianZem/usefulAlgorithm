#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

enum {
    HZ_500 =   500,
    HZ_1K  =  1000,
    HZ_2K  =  2000,
    HZ_3K  =  3000,
    HZ_4K  =  4000,
    HZ_5K  =  5000,
    HZ_6K  =  6000,
    HZ_7K  =  7000,
    HZ_8K  =  8000,
    HZ_10K = 10000,
    HZ_15K = 15000,
    HZ_20K = 20000,
};

const char* outputFileName = "test.pcm"; // output file(raw-data)
const int   SAMPLE_RATE    =      16000; // Hz
const int    MAX_VOLUME    =     0x7FFF; // signed 16 bit
const int   PLAY_TIME_S    =          3; // seconds

int main() {

    FILE *fout = fopen(outputFileName, "w");

    for(int pt = 0; pt < SAMPLE_RATE * PLAY_TIME_S; pt++) {
        double volume = MAX_VOLUME * 0.8;
        double sample = 2.0 * M_PI * HZ_5K * pt / SAMPLE_RATE;

        int musicValue = volume * sin (sample); // Asin(B) || A : volume, B : frequency

        fprintf(fout, "%c", musicValue & 0xFF);
        fprintf(fout, "%c", (musicValue >> 8) & 0xFF);
    }

    fclose(fout);
}

