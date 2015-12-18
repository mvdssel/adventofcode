#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    // MFCSAM-scan
    unordered_map<string, int> MFCSAMScan
    {
        {"children", 3},
        {"cats", 7},
        {"samoyeds", 2},
        {"pomeranians", 3},
        {"akitas", 0},
        {"vizslas", 0},
        {"goldfish", 5},
        {"trees", 3},
        {"cars", 2},
        {"perfumes", 1}
    };

    // Input stream
    const string input = "input.txt";
    fstream ifs(input, fstream::in);

    // Extraction variables
    regex rgx("Sue (\\d+): (\\w+): (\\d+), (\\w+): (\\d+), (\\w+): (\\d+)");
    smatch match;
    string line;

    vector<int> solutions;

    // Read input stream
    while(getline(ifs, line)) {
        if(regex_search(line, match, rgx)) {
            if(MFCSAMScan[match[2]] == stoi(match[3]) &&
               MFCSAMScan[match[4]] == stoi(match[5]) &&
               MFCSAMScan[match[6]] == stoi(match[7]))
            {
                solutions.push_back(stoi(match[1]));
            }
        }
        else {
            cout << "wtf" << endl;
        }
    }

    cout << "These Sues seem to meet my MFCSAMScan: ";
    auto it = solutions.begin();
    cout << (*it++);
    while(it != solutions.end()) {
        cout << ", " << (*it++);
    }
    cout << endl;

    return 0;
}
