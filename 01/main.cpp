#include <iostream>
    using std::cout;
    using std::endl;
#include <fstream>
    using std::fstream;
#include <string>
    using std::string;

int main(int argc, char** argv) {
    const char* filename = "input.txt";

    int elevation = 0;
    int pos = 1;
    bool enteredBasement = false;

    char ch;
    fstream fin(filename, fstream::in);

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
