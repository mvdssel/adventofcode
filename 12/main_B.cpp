#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <cctype>
#include <functional>
#include "./jsoncpp/dist/json/json.h"

using namespace std;

int main(int argc, char *argv[]) {
    const string input = "input.txt";
    fstream ifs(input, fstream::in);
    Json::Value root;
    ifs >> root;

    stack<Json::Value> toCheck;
    toCheck.push(root);

    int total = 0;
    Json::Value curObj;
    int curTotal = 0;
    bool skip = false;
    vector<Json::Value> toCheckIfNoRed;

    function<void(const Json::Value &)> handleValue = [&] (const Json::Value &val) {
        if(val.isString()) {
            try {
                curTotal += stoi(val.asString());
                // cout << "\tfound int" << endl;
            } catch (const invalid_argument &ia) {
                if(curObj.isObject() && val.asString().compare("red") == 0) {
                    // cout << "\tfound red" << endl;
                    skip = true;
                }
            }
        }
        else if (val.isInt()) {
            // cout << "\tfound int" << endl;
            curTotal += val.asInt();
        }
        else {
            // cout << "\tfound useless" << endl;
        }
    };

    // Loop over the entire JSON structure
    while(!toCheck.empty()) {
        curObj = toCheck.top();
        toCheck.pop();

        // cout << "in object: " << curObj.isObject() << endl;

        // Loop over the object
        Json::Value::iterator curObjIt = curObj.begin();
        while(curObjIt != curObj.end() && !skip) {
            if(curObjIt->isArray() || curObjIt->isObject()) {
                // cout << "\tfound " << (curObjIt->isArray() ? "array" : "obj") << endl;
                toCheckIfNoRed.push_back(*curObjIt);
            }
            else if(curObj.isObject()) {
                handleValue(curObjIt.key());
                handleValue(*curObjIt);
            }
            else { // curObj == array
                handleValue(*curObjIt);
            }
            curObjIt++;
        }

        if(!skip) {
            for(vector<Json::Value>::const_iterator it = toCheckIfNoRed.begin();
                it != toCheckIfNoRed.end(); it++)
            {
                toCheck.push(*it);
            }
            total += curTotal;
        }

        curTotal = 0;
        skip = false;
        toCheckIfNoRed.clear();
    }


    cout << "We found a total of " << total << " bright stars!" << endl;
}
