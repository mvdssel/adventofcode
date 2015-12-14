#include <iostream>
    using std::cout;
    using std::endl;
#include <fstream>
    using std::fstream;
#include <set>
    using std::set;
#include <utility>
    using std::pair;
    using std::make_pair;

int main(int argc, char** argv) {
    const char* filename = "input.txt";

    fstream ifs(filename, fstream::in);
    char ch;

    set<pair<int, int> > positions;
    pair<int, int> curPos = make_pair(0, 0);
    positions.insert(curPos);

    while(ifs.get(ch)) {
        if(ch == '<')      curPos.first--;
        else if(ch == '>') curPos.first++;
        else if(ch == '^') curPos.second++;
        else if(ch == 'v') curPos.second--;

        positions.insert(curPos);
    }

    cout << "We visited " << positions.size() << " different houses this night!" << endl;

    return 0;
} 
