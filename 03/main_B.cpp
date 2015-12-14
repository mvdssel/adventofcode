#include <iostream>
    using std::cout;
    using std::endl;
#include <fstream>
    using std::fstream;
#include <set>
    using std::set;
#include <array>
    using std::array;
#include <utility>
    using std::pair;
    using std::make_pair;

int main(int argc, char** argv) {
    const char* filename = "input.txt";

    fstream ifs(filename, fstream::in);
    char ch;

    array<pair<int, int>, 2> curPos = {{
        make_pair(0, 0),
        make_pair(0, 0)
    }};
    bool santaMoves = true;

    set<pair<int, int> > positions;
    positions.insert(curPos[0]);

    while(ifs.get(ch)) {
        if(ch == '<')      curPos[santaMoves].first--;
        else if(ch == '>') curPos[santaMoves].first++;
        else if(ch == '^') curPos[santaMoves].second++;
        else if(ch == 'v') curPos[santaMoves].second--;

        positions.insert(curPos[santaMoves]);
        santaMoves = !santaMoves;
    }

    cout << "We visited " << positions.size() << " different houses this night!" << endl;

    return 0;
} 
