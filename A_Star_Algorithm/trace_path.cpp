#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

enum {
    EMPTY    = 0,
    OBSTACLE = 1
};

int mapState[160][90];
int fromI = 1, fromJ = 1, goalI = 3, goalJ = 3;

bool isOutofBound(int i, int j) {
    return i < 0 || i >= 160 || j < 0 || j >= 90;
}

class Cell {
    public :
        int i, j;
        // GScore : 이 Cell까지 걸린 비용
        mutable int GScore;
        mutable int pi, pj;

        Cell(int i = 0, int j = 0) : i(i), j(j) {} 
        int getH() const {
            return 1 * (abs(goalI - i) + abs(goalJ - j));
        } 
        int getF() const {
            return getH() + GScore;
        }
        bool operator<(const Cell& h) const {
            return !(getF() < h.getF());
        }
}; 

struct SetComparer {
    bool operator() (const Cell& lhs, const Cell& rhs) const {
        if(lhs.i == rhs.i) return lhs.j < rhs.j; 
        return lhs.i < rhs.i;
    }
};

vector<pair<int, int>> astar() {

    vector<pair<int, int>> result;
    if( mapState[fromI][fromJ] == OBSTACLE || mapState[goalI][goalJ] == OBSTACLE )
        return result;

    const int nextPosition[8][3] = {
        {-1, -1, 14}, {-1,  1, 14}, { 1, -1, 14}, { 1,  1, 14}, // unused
        {-1,  0, 10}, { 1,  0, 10}, { 0, -1, 10}, { 0,  1, 10}  // used
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
        for(int pos=4; pos<8; pos++) {
            int i = beforeCell.i + nextPosition[pos][0];
            int j = beforeCell.j + nextPosition[pos][1];

            if( !isOutofBound(i, j) ) {
                if( mapState[i][j] == OBSTACLE ) continue;

                // set nextCell values | parent : beforeCell
                Cell nextCell;
                nextCell.i = i; nextCell.j = j;
                nextCell.GScore = beforeCell.GScore + nextPosition[pos][2];
                nextCell.pi = beforeCell.i;
                nextCell.pj = beforeCell.j; 

                set<Cell>::iterator iter = closedSet.find( nextCell );
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
            result.push_back( make_pair(traceI, traceJ) );
            auto toFindParent = closedSet.find(Cell(traceI, traceJ));
            traceI = toFindParent->pi; traceJ = toFindParent->pj;
        }
        result.push_back( make_pair(fromI, fromJ) );
    } 
    return result;
}

int main() {
    /*
     *  -- Map Example --
     * |  0  0  0  0  0  |
     * |  0  S  1  0  0  |
     * |  0  1  1  1  0  |
     * |  0  0  1  E  0  |
     * |  0  0  0  0  0  |
     *  -----------------
     */
    mapState[1][2] = mapState[3][2] = OBSTACLE;
    mapState[2][1] = mapState[2][2] = OBSTACLE;
    mapState[2][2]                  = OBSTACLE;

    vector<pair<int, int>> pv = astar();
    for(vector<pair<int, int>>::reverse_iterator rit = pv.rbegin(); rit != pv.rend(); rit++) {
        cout << rit->first << " " << rit->second << "\n";
    }
}


