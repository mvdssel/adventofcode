#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>

using namespace std;

const string input = "input.txt";
// const string input = "test.txt";
const string startMolecule = "e";

set<string> getReplacements(const string &startMolecule, const unordered_multimap<string, string> &replacements) {
    set<string> molecules;

    for(const auto &replacement : replacements) {
        // prepare while
        string sample(startMolecule);
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
            sample = startMolecule;
            searchIndex = replacementIndex + 1;
            replacementIndex = sample.find(replacement.first, searchIndex);
        }
    }

    return molecules; // uses RVO
}

struct lenCompare {
    bool operator() (const string& a, const string& b) const{
        return a.size() > b.size();
    }
};

int main(int argc, char *argv[]) {
    fstream ifs(input, fstream::in);
    string from, s, to;

    multimap<string, string, lenCompare> replacements;
    while(ifs >> from >> s >> to) {
        replacements.insert(make_pair(to, from));
    }

    for(auto v : replacements) {
        cout << v.first << ":" << v.second << endl;
    }

    while(:qa
    
    // const string medicineMolecule = from;
    //
    // multimap<int, string> newMolecules; // <steps to produce, molecule>
    // newMolecules.insert(make_pair(0, startMolecule));
    //
    // bool found = false;
    //
    // while(!newMolecules.empty() && !found) {
    //     map<int, string>::iterator researchedMol = newMolecules.begin();
    //     set<string> resultMolecules = getReplacements(researchedMol->second, replacements);
    //
    //     for(const string &result : resultMolecules) {
    //         if(result.size() < medicineMolecule.size()) {
    //             newMolecules.insert(make_pair(researchedMol->first + 1, result));
    //         }
    //         else if(result.size() == medicineMolecule.size() && result.compare(medicineMolecule) == 0) {
    //             found = true;
    //             cout << "Created " << result << " in " << (researchedMol->first + 1) << " steps!" << endl;
    //         }
    //         // else: already researched or exceeding size of the target molecule
    //     }
    //
    //     newMolecules.erase(researchedMol);
    // }
    //
    // return 0;
}
