#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <iomanip>

using namespace std;

int main(int argc, char **argv) {
    const char *input = "input.txt";
    fstream ifs(input, fstream::in);
    string line;

    map<regex *, string> replaces;
    replaces.insert(make_pair(new regex("\\\\"), "\\\\"));
    replaces.insert(make_pair(new regex("\""), "\\\""));
    replaces.insert(make_pair(new regex("^(.*)$"), "\"$1\""));

    int total = 0;

    while(getline(ifs, line)) {
        total -= line.size();

        // cout << setw(50) << line << " " << line.size() << " ";

        for_each(replaces.begin(), replaces.end(), [&line] (pair<regex *, string> replace) {
                line = regex_replace(line, *(replace.first), replace.second);
        });

        // cout << line.size() << " " << line << endl;

        total += line.size();
    }

    cout << "We increased the length of all our strings with " << total << " characters!" << endl;

    return 0;
}
