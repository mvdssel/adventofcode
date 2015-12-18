#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

template <typename T>
ostream& operator << (ostream &os, const vector<T> &v) {
    auto it = v.begin();
    while(it != v.end()) {
        cout << (*it++) << " ";
    }
    return os;
}

struct candidate {
    int capacity;                 // acquired capacity from previously added containers
    int searchIndex;              // from where do we start searching for extra containers
};

int main(int argc, char *argv[]) {
    const int requiredCapacity = 150;

    // Reading all container sizes
    const string input = "input.txt";
    fstream ifs(input, fstream::in);
    int containerSize;
    vector<int> containers;
    while(ifs >> containerSize) containers.push_back(containerSize);

    int solutionCnt = 0;

    stack<candidate> incomplSearches;
    incomplSearches.push((candidate){0, 0});
    while(!incomplSearches.empty()) {
        const candidate prevSearch = incomplSearches.top();
        incomplSearches.pop();

        // Search for extra containers that can be added to the candidate solution
        for(int i = prevSearch.searchIndex; i < containers.size(); i++) {
            candidate newSearch = {
                prevSearch.capacity + containers[i],
                i + 1
            };

            if(newSearch.capacity == requiredCapacity) {
                solutionCnt++;
                // don't serach any further, will only exceed the required capacity
            }
            else if(newSearch.capacity < requiredCapacity) {
                incomplSearches.push(newSearch);
            }
            // else: already exceeded the required capacity, so stop searching
        }
    }

    cout << "We found " << solutionCnt << " awesome container solutions!" << endl;


    return 0;
}
