#include <iostream>
    using std::cout;
    using std::endl;
#include <string>
    using std::string;
#include <fstream>
    using std::fstream;
#include <regex>
    using std::regex;
    using std::regex_search;

const char* filename = "input.txt";

int main(int argc, char** argv) {
    fstream ifs(filename, fstream::in);
    string candidate;

    regex doublePairRgx("(..).*\\1");
    regex letterRepeatRgx("(.).\\1");

    int niceCnt = 0;

    while(getline(ifs, candidate)) {
        if(regex_search(candidate, doublePairRgx) && 
           regex_search(candidate, letterRepeatRgx)) {
            niceCnt++;
            // cout << candidate << endl;
        }
    }

    cout << "We found " << niceCnt << " nice strings!" << endl;

    return 0;
} 
