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

    // continue from the second char
    int total = 1;
    for(int i = 1; i < input.size(); i++) {
        if(input[i-1] == input[i])
            total++;
        else {
            output << total << input[i-1];
            total = 1;
        }
    }

    // also append the last check
    output << total << input[input.size() - 1];

    return output.str();
}
