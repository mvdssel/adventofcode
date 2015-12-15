#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>
#include <set>

using namespace std;

template <typename T>
void print(const vector<T> &v) {
    for_each(v.begin(), v.end(), [] (string val) {
        cout << val << " ";
    });
    cout << endl;
}

int main(int argc, char **argv) {
    const string input = "input.txt";
    fstream ifs(input, fstream::in);
    string cmd;

    regex cmdRgx("(\\w+) to (\\w+) = (\\d+)");
    smatch cmdMatch;
    string from, to;
    int distance;

    map<pair<string, string>, int> distances;
    set<string> s_cities;

    while(getline(ifs, cmd)) {
        if(regex_search(cmd, cmdMatch, cmdRgx)) {
            try {
                // Extract information
                distance = stoi(cmdMatch[3]);
                from = cmdMatch[1];
                to = cmdMatch[2];

                // Save information
                s_cities.insert(from);
                s_cities.insert(to);
                distances[make_pair(from, to)] = distance;
                distances[make_pair(to, from)] = distance;
            } catch (const std::invalid_argument& ia) {
                cout << "Could not parse distance: " << cmdMatch[3] << endl;
            }
        }
        else {
            cout << "Could not parse command: " << cmd << endl;
        }
    }
    
    // Create a vector which can be permutated (is already sorted)
    vector<string> v_cities(s_cities.begin(), s_cities.end()),
                   solution(v_cities.size());

    // Loop over all permutations
    int minDistance = numeric_limits<int>::max();
    do {
        int currDistance = 0;

        vector<string>::const_iterator it = v_cities.begin();
        while(it + 1 < v_cities.end() && currDistance < minDistance) {
            currDistance += distances[make_pair(*(it), *(it+1))];
            it++;
        }

        if(currDistance < minDistance) {
            minDistance = currDistance;
            copy(v_cities.begin(), v_cities.end(), solution.begin());
        }
    } while(next_permutation(v_cities.begin(), v_cities.end()));

    cout << "We only needed to travel " << minDistance << " miles!" << endl;
    print(solution);

    return 0;
}
