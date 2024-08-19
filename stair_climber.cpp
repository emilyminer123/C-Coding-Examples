/*******************************************************************************
 * Name        : stair_climber.cpp
 * Description : Lists the number of ways to climb n stairs.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Calculates all the ways to climb `num_stairs`
vector< vector<int> > get_ways(int num_stairs) {
    vector<vector<int>> ways;
    
    if (num_stairs <= 0){
        ways.push_back(vector<int>());
    }

    for (int i = 1; i < 4; i++) {
        if(num_stairs >= i) {
            vector<vector<int>> result = get_ways(num_stairs - i);
            for (size_t j = 0; j < result.size(); j++) {
                result[j].push_back(i);
            }
            ways.insert(ways.end(), result.begin(), result.end());
        }
    }
    
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    int spaces;
    int iterator = 0;

    // Find proper spacing for displaying the count
    if (ways.size() > 0) {
        spaces = (int)log10((double)ways.size()) + 1;
    } else {
        spaces = 1;
    }

    // Format the output and print it
    for (vector<vector<int>>::const_iterator i = ways.begin(); i != ways.end(); i++) {
        iterator++;
        cout << setw(spaces) << iterator << ". " << "[";

        for (vector<int>::const_reverse_iterator k = i->rbegin(); k != i->rend(); ++k) {
            cout << *k;
            if (k != i->rend()-1) {
                cout << ", ";
            }
        }

        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    
    if (argc > 2 || argc <2){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 0;
    }

    istringstream stream;
    int steps;
    stream.str(argv[1]);

    if (!(stream >> steps) || (steps < 1)) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 0;
    }

    vector<vector<int>> vectorofsteps = get_ways(steps);

    if (steps == 1) {
        cout << "1 way to climb 1 stair." <<endl;
    } else {
        cout << vectorofsteps.size() << " ways to climb " << steps << " stairs." << endl;
    }

    display_ways(vectorofsteps);
    return 0;
}
