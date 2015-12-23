#include <iostream>
#include <vector>
#include <fstream>
#include <array>

using namespace std;

const string input = "input.txt";
const int SIZE = 100;
const int STEPS = 100;
// const string input = "test.txt";
// const int SIZE = 6;
// const int STEPS = 5;

typedef array<array<bool, SIZE>, SIZE> LightGrid;

struct pos {
    int x, y;
};

void constructLightGrid(fstream &ifs, LightGrid &grid) {
    char c;

    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            if(ifs >> c) {
                if(c == '#')
                    grid[x][y] = 1;
                else if (c == '.')
                    grid[x][y] = 0;
                else
                    cout << "that's strange...  <" << c << ">" << endl;
            }
            else
                cout << "out of characters..." << endl;
        }
    }
}

ostream& operator << (ostream &os, const pos &p) {
    cout << '(' << p.x << ',' << p.y << ')' << '\t';
    return os;
}

template <typename T>
ostream& operator << (ostream &os, const vector<T> &v) {
    for(const auto &val : v) {
        cout << val << '\t';
    }
    return os;
}

ostream& operator << (ostream &os, const LightGrid &grid) {
    for(int x = 0; x < SIZE; x++) {
        for(int y = 0; y < SIZE; y++) {
            cout << grid[x][y] << " ";
        }
        cout << endl;
    }
    return os;
}

vector<pos> getNeighbours(const pos &p) {
    vector<pos> neighbours;
    vector<int> deltas{-1, 0, 1};

    for(const auto &dx : deltas) {
        for(const auto &dy : deltas) {
            int x = p.x + dx,
                y = p.y + dy;
            if(x >= 0 && x < SIZE &&
               y >= 0 && y < SIZE &&
               !(p.x == x && p.y == y)
            ) {
                neighbours.push_back({x, y});
            }
        }
    }

    return neighbours; // uses RVO
}

bool isCorner(const pos &p) {
    return (p.x == 0 || p.x == SIZE - 1) &&
           (p.y == 0 || p.y == SIZE - 1);
}

bool processLight(const LightGrid &grid, const pos &p) {
    if(isCorner(p)) return true;

    vector<pos> neighbours = getNeighbours(p);
    int neighboursOn = 0;
    for(const auto &n : neighbours) {
        neighboursOn += grid[n.x][n.y];
    }

    if(grid[p.x][p.y]) {
        return neighboursOn == 2 || neighboursOn == 3;
    }
    else {
        return neighboursOn == 3;
    }
}

int countOn(const LightGrid &grid, const pos &begin = {0, 0}, const pos &end = {SIZE, SIZE}) {
    int cnt = 0;
    for(int x = begin.x; x < end.x; x++) {
        for(int y = begin.y; y < end.y; y++) {
            cnt += grid[x][y];
        }
    }
    return cnt;
}

int main(int argc, char *argv[]) {
    fstream ifs(input, fstream::in);

    LightGrid currentGrid,
              newGrid;
    constructLightGrid(ifs, currentGrid);

    for(int x = 0; x < SIZE; x++) {
        for(int y = 0; y < SIZE; y++) {
            if(isCorner({x, y})) currentGrid[x][y] = true;
            newGrid[x][y] = currentGrid[x][y];
        }
    }

    // cout << countOn(currentGrid) << endl;
    
    for(int i = 0; i < STEPS; i++) {
        for(int x = 0; x < SIZE; x++) {
            for(int y = 0; y < SIZE; y++) {
                newGrid[x][y] = processLight(currentGrid, {x, y});
            }
        }
        currentGrid.swap(newGrid);
        // cout << currentGrid << endl;
    }

    cout << "We lit about a " << countOn(currentGrid) << " bright stars!" << endl;



    return 0;
}
