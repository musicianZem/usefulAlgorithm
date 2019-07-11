#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int obstacle[160][90];
int fromI = 0, fromJ = 0, goalI = 15, goalJ = 8;
bool hasPath = true;
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


vector<pair<int, int>> astar();

int main() {
    vector< pair<int, int> > pv = astar();
    for(vector< pair<int, int> >::reverse_iterator rit = pv.rbegin(); rit != pv.rend(); rit++) {
        cout << rit->first << " " << rit->second << "\n";
    }
}

vector<pair<int, int>> astar() {

    const int nextPosition[8][3] = {
        {-1, -1, 3}, {-1,  1, 3}, { 1, -1, 3}, { 1,  1, 3},
        {-1,  0, 2}, { 1,  0, 2}, { 0, -1, 2}, { 0,  1, 2}
    };

    Cell firstCell( fromI, fromJ );
    firstCell.GScore = 0;
    firstCell.pi = fromI; firstCell.pj = fromJ;
    std::set<Cell, SetComparer> closedSet;
    closedSet.insert( firstCell );
    std::priority_queue<Cell> queueO;
    std::set<Cell, SetComparer> openSet; 
    openSet.insert(firstCell);
    queueO.push(firstCell);

    while(!queueO.empty()) {
        Cell beforeCell = queueO.top();
        queueO.pop();
        closedSet.insert(beforeCell);
        if(beforeCell.i == goalI && beforeCell.j == goalJ) {
            break;
        }
        for(int pos=4; pos<8; pos++) {
            int i = beforeCell.i + nextPosition[pos][0];
            int j = beforeCell.j + nextPosition[pos][1];
            if( !isOutofBound(i, j) ) {
                if( obstacle[i][j] == 1 ) continue;
                Cell nextCell;
                nextCell.i = i; nextCell.j = j;
                nextCell.GScore = beforeCell.GScore + nextPosition[pos][2];
                nextCell.pi = beforeCell.i;
                nextCell.pj = beforeCell.j; 
                if(closedSet.find(nextCell) == closedSet.end()) {
                    auto iter = openSet.find(nextCell);
                    obstacle[i][j] = -2;
                    if(iter != openSet.end()) {
                        if(iter->getF() > nextCell.getF()) {
                            iter->pi = beforeCell.i;
                            iter->pi = beforeCell.j;
                            iter->GScore = beforeCell.GScore + nextPosition[pos][2]; 
                        }
                    }
                    else {
                        openSet.insert(nextCell); 
                        queueO.push(nextCell); 
                    }
                }
            }
        } 
    }

    auto iter = closedSet.find(Cell(goalI, goalJ));
    obstacle[goalI][goalJ] = 0;

    vector<pair<int, int>> result;
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

