#include <iostream>
    using std::cout;
    using std::endl;
    using std::getline;
#include <string>
    using std::string;
    using std::stoi;
#include <fstream>
    using std::fstream;
#include <regex>
    using std::regex;
    using std::regex_search;
    using std::smatch;
#include <algorithm>
    using std::min;
#include <array>
    using std::array;
    using std::sort;

int main(int argc, char** argv) {
    const char* filename = "input.txt";

    fstream ifs(filename, fstream::in);
    string line;

    smatch lwhMatch;
    regex lwhRegex("(\\d+)x(\\d+)x(\\d+)");

    array<int, 3> dim;
    int totalWrapping = 0;
    int totalRibbon = 0;

    while(std::getline(ifs, line)) {
        if(regex_search(line, lwhMatch, lwhRegex)) {
            dim = {
                stoi(lwhMatch[1]),
                stoi(lwhMatch[2]),
                stoi(lwhMatch[3])
            };
            sort(dim.begin(), dim.end());


            totalWrapping += 2*dim[0]*dim[1] + 2*dim[1]*dim[2] + 2*dim[0]*dim[2] + dim[0]*dim[1];
            totalRibbon += 2*dim[0] + 2*dim[1] + dim[0]*dim[1]*dim[2];
        }
    }

    cout << "We need " << totalWrapping << " square meter of wrapping paper!" << endl;
    cout << "We need " << totalRibbon << " meters of ribbon!" << endl;

    return 0;
}
