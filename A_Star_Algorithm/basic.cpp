#include <iostream>
#include <vector>   // vector<> for print result
#include <queue>    // priority_queue<>
#include <cmath>    // using M_PI
#include <set>      // set<>

const int OBSTACLE = 1;
const int HEIGHT = 100;
const int WIDTH  = 100;
int mapState[HEIGHT][WIDTH];

bool isOutofBound(int i, int j) {
    return i < 0 || i >= HEIGHT || j < 0 || j >= WIDTH;
}

class Cell {
    public :
        int i, j;
        int currentDist  = 0;
        int expectedDist = 0;

        const double getExpectedDist() const {
            return currentDist + expectedDist;
        }

        void calculateExpectedDist(int endI, int endJ) {
            expectedDist = abs(endI-i) + abs(endJ-j);
        }

        Cell(int i=0, int j=0) : i(i), j(j) { }
};

struct CompareCellByDist {
    bool operator() (const Cell& c1, const Cell& c2) {
        return c1.getExpectedDist() < c2.getExpectedDist();
    }
};

struct CompareCellByIndex {
    bool operator() (const Cell& c1, const Cell& c2) {
        if( c1.i != c2.i ) return c1.i < c2.i;
        return c1.j < c2.j;
    }
};

void astar(int startI, int startJ, int endI, int endJ) {
    const int nextPosition[4][2] = {
        {-1,  0},
        { 1,  0},
        { 0, -1},
        { 0,  1}
    };

    Cell firstCell( startI, startJ );
    firstCell.calculateExpectedDist(endI, endJ);

    std::set<Cell, CompareCellByDist  > openList;
    std::set<Cell, CompareCellByIndex > closedList;

    openList.insert( firstCell );

    while( !openList.empty() ) {
        Cell nearestCell = *openList.begin();
        openList.erase(openList.begin());
        closedList.insert( nearestCell );

        if( nearestCell.i == endI && nearestCell.j == endJ ) {
            break;
        }

        for(int p = 0; p < 4; p++) {
            int i = nearestCell.i + nextPosition[p][0];
            int j = nearestCell.j + nextPosition[p][1];

            if( !isOutofBound(i, j) ) {
                if( mapState[i][j] == OBSTACLE ) continue;

                Cell nextCell( i, j );
                nextCell.currentDist = nearestCell.currentDist + 1;
                nextCell.calculateExpectedDist(endI, endJ);

                if( closedList.find( nextCell ) == closedList.end() ) {
                    openList.insert( nextCell );
                }
            
            }
        }
    }
}

int main() {
    astar(1, 1, 3, 3);
}
