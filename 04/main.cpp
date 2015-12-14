#include <iostream>
    using std::cout;
    using std::endl;
#include <string>
    using std::string;
#include <sstream>
    using std::stringstream;

#include "hashlib2plus/trunk/src/hashlibpp.h"

const string secret = "ckczppom";

void findHashWithPrefix(const string &secret, const string &hashPrefix);

int main(int argc, char** argv) {
    findHashWithPrefix(secret, "00000");

    cout << endl;

    findHashWithPrefix(secret, "000000");

    return 0;
}


void findHashWithPrefix(const string &secret, const string &hashPrefix) {
    hashwrapper *md5Wrapper = new md5wrapper();
    stringstream msg;
    string digest;
    int msgPostfix = 0;

    // Find hash
    while(digest.find(hashPrefix) != 0) {
        // Create message
        msgPostfix++;
        msg.str("");
        msg.clear();
        msg << secret << msgPostfix;

        // Create md5 hash
        digest = md5Wrapper->getHashFromString(msg.str());
    }

    cout << "secret:  " << secret << endl;
    cout << "postfix: " << msgPostfix << endl;
    cout << "message: " << msg.str() << endl;
    cout << "digest:  " << digest << endl;

    // Cleaning up
    delete md5Wrapper;
}
