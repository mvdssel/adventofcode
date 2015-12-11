#include <iostream>
    using std::cout;
    using std::endl;
#include <fstream>
    using std::fstream;
#include <string>
    using std::string;

int main(int argc, char** argv) {
    const string filename = "input.txt";

    char ch;
    int elevation = 0;
    int pos = 1;
    bool enteredBasement = false;

    fstream fin(filename.c_str(), fstream::in);
    while (fin >> ch) {
        if(ch == '(') elevation++;
        if(ch == ')') elevation--;

        if(!enteredBasement && elevation == -1) {
            cout << "Entering basement on position " << pos << "." << endl;
            enteredBasement = true;
        }
        pos++;
    }

    cout << "Delivering package to floor " << elevation << "." << endl;

    return 0;
}
