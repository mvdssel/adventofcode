#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

using namespace std;

template <typename T, typename S>
ostream& operator << (ostream &os, const unordered_map<T, S> &m) {
    auto it = m.begin();
    while(it != m.end()) {
        os << setw(10) << it->first << ": " << setw(3) << it->second << "\t";
        it++;
    }
    return os;
}

template <typename T>
ostream& operator << (ostream &os, const vector<T> &v) {
    auto it = v.begin();
    while(it != v.end()) {
        os << setw(3) << *it << " ";
        it++;
    }
    return os;
}

int main(int argc, char *argv[]) {
    // Input stream
    const string input = "input.txt";
    fstream ifs(input, fstream::in);

    // Extraction variables
    regex rgx("(\\w+): .* (-?\\d+), .* (-?\\d+), .* (-?\\d+), .* (-?\\d+), .* (-?\\d+)");
    smatch match;
    string line;

    unordered_map<string, unordered_map<string, int>> ingredients;

    // Read input stream
    while(getline(ifs, line)) {
        if(regex_search(line, match, rgx)) {
            string ingredient = match[1];

            unordered_map<string, int> stats;
            stats.insert(make_pair("capacity", stoi(match[2])));
            stats.insert(make_pair("durability", stoi(match[3])));
            stats.insert(make_pair("flavor", stoi(match[4])));
            stats.insert(make_pair("texture", stoi(match[5])));
            stats.insert(make_pair("calories", stoi(match[6])));

            ingredients.insert(make_pair(ingredient, stats));
        }
        else {
            cout << "wtf" << endl;
        }
    }

    int maxScore = 0;
    vector<int> solution(4);

    for(int i = 1; i <= 100-3; i ++) {
        for(int j = 1; j <= 100-2 - i; j ++) {
            for(int l = 1; l <= 100-1-i-j; l ++) {
                int k = 100 - i - j - l;
                vector<int> amounts({i, j, l, k});

                int cap = 0, dur = 0, fla = 0, tex = 0, cal = 0;

                auto ingrIt = ingredients.begin();
                auto amntIt = amounts.begin();
                while(ingrIt != ingredients.end() && amntIt != amounts.end()) {
                    cap += ingrIt->second["capacity"] * (*amntIt);
                    dur += ingrIt->second["durability"] * (*amntIt);
                    fla += ingrIt->second["flavor"] * (*amntIt);
                    tex += ingrIt->second["texture"] * (*amntIt);
                    cal += ingrIt->second["calories"] * (*amntIt);

                    ingrIt++;
                    amntIt++;
                }

                int cookieScore = max(0, cap) *
                                  max(0, dur) *
                                  max(0, fla) *
                                  max(0, tex);
                if(cookieScore > maxScore && cal == 500) {
                    maxScore = cookieScore;
                    copy(amounts.begin(), amounts.end(), solution.begin());
                }

            }
        }
    }

    cout << "We made baked cookies with a monster score of the " << maxScore << " cookie points!" << endl;

    return 0;
}
