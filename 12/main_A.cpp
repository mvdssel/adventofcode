#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <cctype>

using namespace std;

int main(int argc, char *argv[]) {
    const string input = "input.txt";
    fstream ifs(input, fstream::in);
    char c;

    int total = 0;
    int current = 0;
    bool negate = false;
    while(ifs.get(c)) {
        if(isdigit(c)) {
            current = (c - '0') + current * 10;
        }
        else if(c == '-') {
            negate = !negate;
        }
        else if(current != 0) {
            if(negate) current = -current;
            total += current;
            current = 0;
            negate = false;
        }
    }

    cout << "We found a total of " << total << " lovely stars!" << endl;
    
    return 0;
}
