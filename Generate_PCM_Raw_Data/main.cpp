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
    C = 1047,
    D = 1175,
    E = 1319,
    F = 1396,
    G = 1568,
    A = 1760,
    B = 1976,
    C1= 2093,
};

const char* outputFileName = "test.pcm"; // output file(raw-data)
const int   SAMPLE_RATE    =      96000; // Hz
const int    MAX_VOLUME    =     0x7FFF; // signed 16 bit

void printFileSpecificHz( FILE *fp, double volume, int hz, int ms ) {
    for(int pt = 0; pt < SAMPLE_RATE * ms/1000 ; pt++) {
        double sample = 2.0 * M_PI * hz * pt / SAMPLE_RATE;

        int musicValue = volume * sin( sample );

        fprintf(fp, "%c", musicValue & 0xFF);
        fprintf(fp, "%c", (musicValue >> 8) & 0xFF);
    }
}

int main() {

    FILE *fout = fopen(outputFileName, "w");

    printFileSpecificHz(fout, MAX_VOLUME * 0.8, C , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, D , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, E , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, F , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, G , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, A , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, B , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, C1, 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.0, C1, 500); // zero volume
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, C1, 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, B , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, A , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, G , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, F , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, E , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, D , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, C , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.0, C , 500); // zero volume
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, C , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, E , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, G , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, C1, 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, G , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, E , 250);
    printFileSpecificHz(fout, MAX_VOLUME * 0.8, C , 750);

    fclose(fout);
}


