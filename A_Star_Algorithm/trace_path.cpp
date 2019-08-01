#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <set>
#include <queue>
#include <cstring>

enum {
    EMPTY    = 0,
    OBSTACLE = 1
};

int WIDTH = 90;
int HEIGHT= 160;
int mapState[160][90];
std::pair<int, int> destination;
std::pair<int, int> curPosition;

class Cell {
    public :
        int i, j;
        // GScore : 이 Cell까지 걸린 비용
        mutable int GScore;
        mutable int pi, pj;

        static int goalI, goalJ;

        Cell(int i = 0, int j = 0) : i(i), j(j) {
        } 

        int getH() const {
            return 1 * (abs(goalI - i) + abs(goalJ - j));
        } 

        int getF() const {
            return getH() + GScore;
        }

        bool operator<(const Cell& h) const {
            return !(getF() < h.getF());
        }

        void static setGoalIdx(int i, int j) {
            goalI = i;
            goalJ = j;
        }
}; 

struct SetComparer {
    bool operator() (const Cell& lhs, const Cell& rhs) const {
        if(lhs.i == rhs.i) return lhs.j < rhs.j; 
        return lhs.i < rhs.i;
    }
};

std::vector<std::pair<int, int>> aStarPath;
int Cell::goalI = 0;
int Cell::goalJ = 0;

void astar() {
    aStarPath.clear();
    int fromI = curPosition.first ;
    int fromJ = curPosition.second;
    int goalI = destination.first ;
    int goalJ = destination.second;

    if( mapState[fromI][fromJ] == OBSTACLE || mapState[goalI][goalJ] == OBSTACLE )
        return;

    Cell::setGoalIdx(goalI, goalJ);

    const int nextPosition[4][3] = { 
        {-1,  0, 1}, { 1,  0, 1}, { 0, -1, 1}, { 0,  1, 1}  // used
    };  

    std::set<Cell, SetComparer> closedSet; // already used set
    std::priority_queue<Cell> openQueue;      // best first

    Cell firstCell( fromI, fromJ );
    firstCell.GScore = 0;
    firstCell.pi = fromI; firstCell.pj = fromJ;

    closedSet.insert(firstCell);
    openQueue.push(firstCell);

    while(!openQueue.empty()) {
        // open pop -> closed push
        Cell beforeCell = openQueue.top();
        openQueue.pop();
        closedSet.insert(beforeCell);

        // find goal -> stop finding
        if(beforeCell.i == goalI && beforeCell.j == goalJ) {
            break;
        }

        // left, right, up, down check
        for(int pos=0; pos<4; pos++) {
            int i = beforeCell.i + nextPosition[pos][0];
            int j = beforeCell.j + nextPosition[pos][1];

            if( i>=0&&j>=0&&i<HEIGHT&&j<WIDTH ) { 
                if( mapState[i][j] == OBSTACLE ) continue;

                // set nextCell values | parent : beforeCell
                Cell nextCell;
                nextCell.i = i; nextCell.j = j;
                nextCell.GScore = beforeCell.GScore + nextPosition[pos][2];
                nextCell.pi = beforeCell.i;
                nextCell.pj = beforeCell.j; 

                std::set<Cell>::iterator iter = closedSet.find( nextCell );
                if(iter != closedSet.end()) {
                    // if visit cell is Used, maintain lower cost Cell
                    if(iter->getF() > nextCell.getF()) {
                        closedSet.erase(iter);
                        closedSet.insert( nextCell );
                        openQueue.push(nextCell);
                    }
                } else {
                    openQueue.push(nextCell); 
                }
            }
        }
    }   

    // make path
    auto iter = closedSet.find(Cell(goalI, goalJ));

    if(iter != closedSet.end()) {
        int traceI = goalI, traceJ = goalJ;
        while( traceI != fromI || traceJ != fromJ ) { 
            aStarPath.push_back( std::make_pair(traceI, traceJ) );
            auto toFindParent = closedSet.find(Cell(traceI, traceJ));
            traceI = toFindParent->pi; traceJ = toFindParent->pj;
        }
        aStarPath.push_back( std::make_pair(fromI, fromJ) );
    }   

    for(std::vector<std::pair<int, int>>::reverse_iterator rit = aStarPath.rbegin(); rit != aStarPath.rend(); rit++) {
        std::cout << rit->first << " " << rit->second << "\n";
    }   
}

int main() {
    memset(mapState, 0, sizeof(mapState));
    curPosition.first =  1;
    curPosition.second=  1;
    for(int i=0; i<50; i++) {
        mapState[5][i] = OBSTACLE;
    }
    destination.first = 10;
    destination.second= 10;
    astar();
}
