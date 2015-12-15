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

#include "node.h"

typedef unsigned short ushort;
typedef Node<ushort> Wire;
Wire* getWire(map<string, Wire *> &wires, const string &identifier);

int main(int argc, char** argv) {
    const char* filename = "input.txt";

    // Open input stream
    fstream ifs(filename, fstream::in);
    string cmd;

    // Wire-map
    map<string, Wire*> wires;

    // Init actions
    map<string, std::function<ushort(Wire *a, Wire *b)>> actions;
    actions.insert(make_pair("",       [] (Wire *a, Wire *b) { return b->getValue();                  }));
    actions.insert(make_pair("NOT",    [] (Wire *a, Wire *b) { return ~b->getValue();                 }));
    actions.insert(make_pair("AND",    [] (Wire *a, Wire *b) { return a->getValue() & b->getValue();  }));
    actions.insert(make_pair("OR",     [] (Wire *a, Wire *b) { return a->getValue() | b->getValue();  }));
    actions.insert(make_pair("RSHIFT", [] (Wire *a, Wire *b) { return a->getValue() >> b->getValue(); }));
    actions.insert(make_pair("LSHIFT", [] (Wire *a, Wire *b) { return a->getValue() << b->getValue(); }));

    // Init regex: a(3        action(4     b(5     dest(6
    regex cmdRgx ("(((\\w+) )?([A-Z]+) )?(\\w+) -> (\\w+)");
    smatch cmdMatch;
    std::function<ushort(Wire *a, Wire *b)> action;
    Wire *a, *b, *dest;

    while(getline(ifs, cmd)) {
        if(regex_search(cmd, cmdMatch, cmdRgx)) {
            // Get the action
            action = actions[cmdMatch[4]];

            // Get a
            try {
                a = new Wire(stoi(cmdMatch[3]));
            } catch (const std::invalid_argument& ia) {
                if(cmdMatch[3].str().empty())
                    a = 0;
                else
                    a = getWire(wires, cmdMatch[3]);
            }

            // Get b
            try {
                b = new Wire(stoi(cmdMatch[5]));
            } catch (const std::invalid_argument& ia) {
                // b cannot be ""
                b = getWire(wires, cmdMatch[5]);
            }

            // Get dest
            dest = getWire(wires, cmdMatch[6]);
            dest->initialize(action, a, b);
        }
    }

    // Part A
    Wire *wireA = wires["a"];
    cout << "We successfully added signal strength " << wireA->getValue() << " on wire 'a'!" << endl;

    // Part B
    Wire *wireB = wires["b"];
    wireB->initialize(actions[""], 0, new Wire(wireA->getValue()));
    for_each(wires.begin(), wires.end(), [] (pair<string, Wire *> val) {
        val.second->reset();
    });
    cout << "We successfully added signal strength " << wireA->getValue() << " on wire 'a'!" << endl;

    // Should delete all nodes...

    return 0;
} 

Wire * getWire(map<string, Wire *> &wires, const string &identifier) {
    Wire *wire = 0;

    map<string, Wire *>::iterator it = wires.find(identifier);
    if(it == wires.end()) {
        wire = new Wire();
        wires.insert(make_pair(identifier, wire));
    }
    else {
        wire = it->second;
    }

    return wire;
}
