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
    regex rgx("(\\w+): (\\d+)");
    smatch match;
    string line;

    vector<int> solutions;
    int auntIndex = 1;

    // Loop over all Sues
    while(getline(ifs, line)) {
        bool auntOk = true;

        // Loop over all things of aunt Sue
        sregex_iterator it(line.begin(), line.end(), rgx), end;
        while(it != end && auntOk) {
            string thing = (*it)[1];
            int amount = stoi((*it)[2]);

            if(thing.compare("cats") == 0 || thing.compare("trees") == 0)
                auntOk = amount > MFCSAMScan[thing];
            else if (thing.compare("pomeranians") == 0 || thing.compare("goldfish") == 0)
                auntOk = amount < MFCSAMScan[thing];
            else
                auntOk = amount == MFCSAMScan[thing];

            it++;
        }

        if(auntOk)
            solutions.push_back(auntIndex);

        auntIndex++;
    }

    cout << "These Sues seem to meet my MFCSAM scan: ";
    auto it = solutions.begin();
    cout << (*it++);
    while(it != solutions.end()) {
        cout << ", " << (*it++);
    }
    cout << endl;

    return 0;
}
