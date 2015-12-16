#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int main(int argc, char *argv[]) {
    const int raceLength = 2503;

    // Input stream
    const string input = "input.txt";
    fstream ifs(input, fstream::in);

    // Extraction variables
    regex rgx("(\\w+) .* (\\d+) .* (\\d+) .* (\\d+)");
    smatch match;
    string line;

    string fastest;
    int maxDistance = 0;

    // Read input stream
    while(getline(ifs, line)) {
        if(regex_search(line, match, rgx)) {
            // Extract information
            int speed = stoi(match[2]),
                runtime = stoi(match[3]),
                resttime = stoi(match[4]);

            // Add full rounds
            int rounds = raceLength / (runtime + resttime);
            int distance = rounds * runtime * speed;
            // Add the last (incomplete) round
            int lastRound = min(raceLength % (runtime + resttime), runtime);
            distance += lastRound * speed;

            if(distance > maxDistance) {
                maxDistance = distance;
                fastest = match[1];
            }
        }
        else { cout << "wtf" << endl; }
    }

    // Print the solution
    cout << fastest << " was " << maxDistance << " km away after " << raceLength << " seconds!" << endl;
    
    return 0;
}

