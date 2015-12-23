#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>

using namespace std;

const string input = "input.txt";
const string startMolecule = "e";

int main(int argc, char *argv[]) {
    fstream ifs(input, fstream::in);
    string from, s, to;

    unordered_multimap<string, string> replacements;
    while(ifs >> from >> s >> to) {
        replacements.insert(make_pair(from, to));
    }
    
    const string medicineMolecule = from;
    
    set<string> molecules;
    for(const auto &replacement : replacements) {
        // prepare while
        string sample(medicineMolecule);
        int searchIndex = 0,
            replacementIndex = sample.find(replacement.first, searchIndex);
        // execute while
        while(replacementIndex != string::npos) {
            molecules.insert(
                sample.replace(
                    replacementIndex,
                    replacement.first.size(),
                    replacement.second));
            // prepare while
            sample = medicineMolecule;
            searchIndex = replacementIndex + 1;
            replacementIndex = sample.find(replacement.first, searchIndex);
        }
    }

    cout << molecules.size() << endl;
    
    return 0;
}
