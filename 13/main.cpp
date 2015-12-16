#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <regex>
#include <functional>

using namespace std;

template <typename T>
void print(const vector<T> &v) {
    for_each(v.begin(), v.end(), [] (string val) {
        cout << val << " ";
    });
    cout << endl;
}

int main(int argc, char *argv[]) {
    // Input stream
    const string input = "input.txt";
    fstream ifs(input, fstream::in);

    // Extraction variables
    regex rgx("^(\\w+) would (gain|lose) (\\d+) .* (\\w+)\\.$");
    smatch match;
    string line;

    // Extraction result
    map<pair<string, string>, int> happinessGrid;
    set<string> s_attendees;

    // Read input stream
    while(getline(ifs, line)) {
        if(regex_match(line, match, rgx)) {
            // Extract information
            string a = match[1],
                   b = match[4];
            int happiness = stoi(match[3]);
            if(match[2].str().compare("lose") == 0) happiness *= -1;

            // Add it to the grid
            happinessGrid.insert(make_pair(make_pair(a, b), happiness));
            s_attendees.insert(a);
            s_attendees.insert(b);
        }
        else { cout << "wtf" << endl; }
    }

    // Add myself
    string me = "Waldo";
    for_each(s_attendees.begin(), s_attendees.end(), [&] (const string &someoneElse) {
        happinessGrid.insert(make_pair(make_pair(me, someoneElse), 0));
        happinessGrid.insert(make_pair(make_pair(someoneElse, me), 0));
    });
    s_attendees.insert(me);

    // Create something that can permutate
    vector<string> v_attendees(s_attendees.begin(), s_attendees.end()), // already sorted because set
                   solution(v_attendees.size());

    // Loop over all permutations
    int maxHappiness = numeric_limits<int>::min();
    do {
        int curHappiness = 0;

        // add all happiness together
        vector<string>::const_iterator it = v_attendees.begin();
        while(it + 1 != v_attendees.end()) {
            curHappiness += happinessGrid[make_pair(*it, *(it+1))];
            curHappiness += happinessGrid[make_pair(*(it+1), *it)];
            it++;
        }
        // a round table...
        curHappiness += happinessGrid[make_pair(v_attendees.front(), v_attendees.back())];
        curHappiness += happinessGrid[make_pair(v_attendees.back(), v_attendees.front())];

        if(curHappiness > maxHappiness) {
            maxHappiness = curHappiness;
            copy(v_attendees.begin(), v_attendees.end(), solution.begin());
        }
    } while(next_permutation(v_attendees.begin(), v_attendees.end()));

    // Print the solution
    cout << "The family feast was as happy as " << maxHappiness << " stars!" << endl;
    print(solution);
    
    return 0;
}
