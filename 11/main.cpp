#include <iostream>
#include <string>
#include <regex>

using namespace std;

void inc(string &str, int i = -1);
bool validate(const string &str);
bool hasStraight(const string &str);
bool hasDoublePair(const string &str);

int main(int argc, char *argv[]) {
    const string input = "hepxcrrq";

    string output = input;

    while(!validate(output)) {
        inc(output);
    }

    cout << "We changed the password to " << output << "!" << endl;

    inc(output);
    while(!validate(output)) {
        inc(output);
    }

    cout << "We changed the password to " << output << "!" << endl;

    return 0;
}

bool validate(const string &str) {
    return hasStraight(str) && hasDoublePair(str);
}

bool hasDoublePair(const string &str) {
    bool check = false;

    regex pairRgx("([a-z])\\1");

    sregex_iterator it(str.begin(), str.end(), pairRgx), end;
    string prev = it->str();
    while(++it != end && !check) {
        check = prev.compare(it->str()) != 0;
    }

    return check;
}

bool hasStraight(const string &str) {
   int i = 1;
   int total = 1;

   while(i < str.size() && total < 3) {
       if(str[i] == str[i - 1] + 1)
           total++;
       else
           total = 1;
       i++;
   }

   return total == 3;
}

void inc(string &str, int i) {
    if(i < 0) i = str.size() - 1;

    if(str[i] == 'z') {
        str[i] = 'a';
        inc(str, i - 1);
    }
    else {
        str[i] = str[i] + 1;
        if(str[i] == 'i' ||
           str[i] == 'l' ||
           str[i] == 'o') {
            inc(str, i);
        }
    }
}
