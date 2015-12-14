#include <iostream>
    using std::cout;
    using std::endl;
#include <string>
    using std::string;
#include <fstream>
    using std::fstream;
#include <regex>
    using std::regex;
    using std::smatch;
    using std::regex_search;
#include <map>
    using std::map;
#include <utility>
    using std::pair;
    using std::make_pair;


const char* filename = "input.txt";
const int LIGHT_CNT = 1000;

int main(int argc, char** argv) {
    // Open input stream
    fstream ifs(filename, fstream::in);
    string cmd;

    // Init light grid
    bool lights[LIGHT_CNT][LIGHT_CNT];
    for(int i = 0; i < LIGHT_CNT; i++) {
        for(int j = 0; j < LIGHT_CNT; j++) {
            lights[i][j] = false;
        }
    }

    // Init actions
    map<string, std::function<void(bool &light)>> actions;
    actions.insert(make_pair("turn on",  [] (bool &light) { light = 1;      }));
    actions.insert(make_pair("turn off", [] (bool &light) { light = 0;      }));
    actions.insert(make_pair("toggle",   [] (bool &light) { light = !light; }));

    // Init regex
    regex cmdRgx ("(.+) (\\d+),(\\d+) through (\\d+),(\\d+)");
    smatch cmdMatch;
    std::function<void(bool &light)> action;
    int x1, y1,
        x2, y2;

    while(getline(ifs, cmd)) {
        if(regex_search(cmd, cmdMatch, cmdRgx)) {
            action = actions[cmdMatch[1]];
            x1 = stoi(cmdMatch[2]);
            y1 = stoi(cmdMatch[3]);
            x2 = stoi(cmdMatch[4]);
            y2 = stoi(cmdMatch[5]);

            for(int x = x1; x <= x2; x++) {
                for(int y = y1; y <= y2; y++) {
                    action(lights[x][y]);
                }
            }
        }
    }

    int totalOn = 0;
    for(int x = 0; x < LIGHT_CNT; x++) {
        for(int y = 0; y < LIGHT_CNT; y++) {
            totalOn += lights[x][y];
        }
    }

    cout << "We lit about " << totalOn << " lights!" << endl;

    return 0;
} 
