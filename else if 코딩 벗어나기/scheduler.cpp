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

class Schedule {
public :
    int dt;
    function<void(void)> func;

    Schedule(int _dt, function<void(void)> _func) {
        dt = _dt;
        func = _func;
    }

    void run() {
        func();
    }
};

class Scheduler {
public :
    queue<Schedule> calender;

    void pushSchedule(Schedule s) {
        calender.push(s);
    }

    void update(int dt) {
        calender.front().run();

        calender.front().dt -= dt;
        if( calender.front().dt < 0 ) {
            calender.pop();
        }
    }

    bool isEmpty() {
        return calender.empty();
    }
};

int main() {
    Scheduler scheduler;
    Car *car = new Car();

    scheduler.pushSchedule( Schedule(1000, [car]() {
        if( car->lspd > 1000 ) car->lspd -= 10;
        if( car->lspd < 1000 ) car->lspd += 10;
        if( car->rspd > 1000 ) car->rspd -= 10;
        if( car->rspd < 1000 ) car->rspd += 10;
    }));

    scheduler.pushSchedule( Schedule(3000, [car]() {
        if( car->lspd > 0 ) car->lspd -= 10;
        if( car->lspd < 0 ) car->lspd += 10;
        if( car->rspd > 500 ) car->rspd -= 10;
        if( car->rspd < 500 ) car->rspd += 10;
    }));

    scheduler.pushSchedule( Schedule(2000, [car]() {
        if( car->lspd > -1000 ) car->lspd -= 10;
        if( car->lspd < -1000 ) car->lspd += 10;
        if( car->rspd > -1000 ) car->rspd -= 10;
        if( car->rspd < -1000 ) car->rspd += 10;
    }));

    while( !scheduler.isEmpty() ) {
        scheduler.update( 20 - rand()%10 + rand()%10 ); /* dt : random almost same with 20 */
        cout << car->lspd << " " << car->rspd << endl;
    }
}
