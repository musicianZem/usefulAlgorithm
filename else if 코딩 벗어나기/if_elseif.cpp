#include <iostream>
#include <queue>
#include <functional>
#include <unistd.h> // timer
#include <cstdlib>

using namespace std;

class Car {
public :
    int lspd;
    int rspd;
    Car(){
        lspd = rspd = 0;
    }
};

int main() {
    Car *car = new Car();
    static int dt_sum = 0;
    while( true ) {
        int dt = 20 - rand()%10 + rand()%10;
        dt_sum += dt;
        if( dt_sum < 1000 )
        {
            if( car->lspd > 1000 ) car->lspd -= 10;
            if( car->lspd < 1000 ) car->lspd += 10;
            if( car->rspd > 1000 ) car->rspd -= 10;
            if( car->rspd < 1000 ) car->rspd += 10;
        }
        else if( dt_sum < 4000 )
        {
            if( car->lspd > 0 ) car->lspd -= 10;
            if( car->lspd < 0 ) car->lspd += 10;
            if( car->rspd > 500 ) car->rspd -= 10;
            if( car->rspd < 500 ) car->rspd += 10;
        }
        else if( dt_sum < 6000 )
        {
            if( car->lspd > -1000 ) car->lspd -= 10;
            if( car->lspd < -1000 ) car->lspd += 10;
            if( car->rspd > -1000 ) car->rspd -= 10;
            if( car->rspd < -1000 ) car->rspd += 10;
        }
        else 
        {
            break;
        }
        cout << car->lspd << " " << car->rspd << endl;
    }
}
