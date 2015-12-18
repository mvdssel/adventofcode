#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const string input = "input.txt";
const int SIZE = 100;

struct dim {
    int x, y;
};

void constructLightGrid(fstream &ifs, bool lightGrid[SIZE][SIZE]) {
    char c;

    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            if(ifs >> c) {
                if(c == '#')
                    lightGrid[x][y] = 1;
                else if (c == '.')
                    lightGrid[x][y] = 0;
                else
                    cout << "that's strange...  <" << c << ">" << endl;
            }
            else
                cout << "out of characters..." << endl;
        }
    }
}

void printLightGrid(bool grid[SIZE][SIZE]) {
    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            cout << grid[x][y] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    fstream ifs(input, fstream::in);
    bool lightGrid[SIZE][SIZE];
    constructLightGrid(ifs, lightGrid);

    printLightGrid(lightGrid);

    return 0;
}
