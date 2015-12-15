#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string lookAndSay(const string &input);

int main(int argc, char **argv) {
    const string input = "1113222113";
    const int ROUNDS = 50;

    string output = input;

    for(int i = 0; i < ROUNDS; i++) {
        output = lookAndSay(output);
    }

    cout << "It became " << output.size() << " characters long!" << endl;
    
    return 0;
}

string lookAndSay(const string &input) {
    stringstream output;

    // make an initial calculation
    char current = input[0];
    int total = 1;

    // continue from the second char
    for(int i = 1; i < input.size(); i++) {
        if(input[i] == current)
            total++;
        else {
            output << total << current;
            current = input[i];
            total = 1;
        }
    }
    // also append the last calculation
    output << total << current;

    return output.str();
}
