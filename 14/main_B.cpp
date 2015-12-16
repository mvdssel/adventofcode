#include <iostream>
#include <fstream>
#include <regex>
#include <map>

using namespace std;

/* Reindeer {{{1 */
class Reindeer {
    enum State { RUNNING, RESTING };

    /* public {{{2 */
    public:
        Reindeer(const string &name, int speed, int runtime, int resttime) :
            name(name), speed(speed), runtime(runtime), resttime(resttime) {
            reset();
        }

        void reset() {
            currentState = RUNNING;
            timeInState = 0;
            distanceTraveled = 0;
            score = 0;
        }

        void advance() {
            if(currentState == RUNNING && timeInState == runtime) {
                currentState = RESTING;
                timeInState = 0;
            }
            else if(currentState == RESTING && timeInState == resttime) {
                currentState = RUNNING;
                timeInState = 0;
            }

            if(currentState == RUNNING) {
                distanceTraveled += speed;
            }
            timeInState++;
        }

        string getName() const {
            return name;
        }

        int getScore() const {
            return score;
        }

        int getDistanceTraveled() const {
            return distanceTraveled;
        }

        void incScore() {
            score++;
        }

    /* private {{{2 */
    private:
        const string name;
        const int speed;
        const int runtime;
        const int resttime;
        State currentState;
        int timeInState;
        int distanceTraveled;
        int score;
    /* 2}}} */
};
/* 1}}} */

int main(int argc, char *argv[]) {
    const int raceLength = 2503;
    // const int raceLength = 1000;

    // Input stream
    const string input = "input.txt";
    // const string input = "test.txt";
    fstream ifs(input, fstream::in);

    // Extraction variables
    regex rgx("(\\w+) .* (\\d+) .* (\\d+) .* (\\d+)");
    smatch match;
    string line;

    vector<Reindeer> reindeers;

    // Read input stream
    while(getline(ifs, line)) {
        if(regex_search(line, match, rgx)) {
            // Extract information
            string name = match[1];
            int speed = stoi(match[2]),
                runtime = stoi(match[3]),
                resttime = stoi(match[4]);

            Reindeer r(name, speed, runtime, resttime);
            reindeers.push_back(r);
        }
        else { cout << "wtf" << endl; }
    }

    // Racing!
    for(int i = 0; i < raceLength; i++) {
        // Remember the fastest of the second
        vector<Reindeer *> fastest;
        int maxDistance = 0;

        // Loop over all reindeers
        for (auto &r : reindeers) {
            // Race
            r.advance();
            
            // Check if fastest
            if(r.getDistanceTraveled() > maxDistance) {
                maxDistance = r.getDistanceTraveled();
                fastest.clear();
                fastest.push_back(&r);
            }
            else if(r.getDistanceTraveled() == maxDistance) {
                fastest.push_back(&r);
            }

            // cout << r.getName() << ":   \t" << r.getDistanceTraveled() << "km\t" << r.getScore() << endl;
        };
        // cout << endl;

        // Award the fastest!
        for(auto r : fastest) {
            r->incScore();
        }
    }

    // Find the fastest reindeer
    const Reindeer *fastest;
    int maxScore = 0;
    for (auto const &r : reindeers) {
        if(r.getScore() > maxScore) {
            maxScore = r.getScore();
            fastest = &r;
        }
    };

    cout << fastest->getName() << " had a score of " << maxScore << " stars after " << raceLength << " seconds!" << endl;
    
    return 0;
}

