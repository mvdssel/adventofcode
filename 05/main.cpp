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

    regex vowelRgx("[aeiou].*[aeiou].*[aeiou]");
    regex doubleRgx("(.)\\1");
    regex badRgx("(ab|cd|pq|xy)");

    int niceCnt = 0;

    while(getline(ifs, candidate)) {
        if(regex_search(candidate, doubleRgx) && 
           regex_search(candidate, vowelRgx)  &&
          !regex_search(candidate, badRgx))
            niceCnt++;
            // cout << candidate << endl;
    }

    cout << "We found " << niceCnt << " nice strings!" << endl;

    return 0;
} 

