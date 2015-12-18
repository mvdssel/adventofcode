#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct candidate {
    int containerCnt;             // amount of containers used to acquire the capacity of this candidate search
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
    int minContainers = numeric_limits<int>::max();

    stack<candidate> incomplSearches;
    incomplSearches.push((candidate){0, 0, 0});
    while(!incomplSearches.empty()) {
        const candidate prevSearch = incomplSearches.top();
        incomplSearches.pop();

        // Search for extra containers that can be added to the candidate solution
        for(int i = prevSearch.searchIndex; i < containers.size(); i++) {
            candidate newSearch = {
                prevSearch.containerCnt + 1,
                prevSearch.capacity + containers[i],
                i + 1
            };

            if(newSearch.capacity == requiredCapacity) {
                if(newSearch.containerCnt == minContainers) {
                    solutionCnt++;
                }
                else if(newSearch.containerCnt < minContainers) {
                    minContainers = newSearch.containerCnt;
                    solutionCnt = 1;
                }
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
