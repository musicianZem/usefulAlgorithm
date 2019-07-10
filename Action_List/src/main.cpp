#include <iostream>
#include <chrono>
#include "action.h"
using namespace std;

int main() {
    /* main loop */

    CuteTrick c("01212");

    while(1) {
        if( c.update() ) break;
    }
}
