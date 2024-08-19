/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Description : Counts the number of inversions in an array.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;

    for (int i =0; i < length-1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] > array[j]) {
                count++;
            } 
        }
    }
    
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
    long numberInversions = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return numberInversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long count = 0;

    if (low < high) {
        int middle = (low + high)/ 2;
        
        count = mergesort(array, scratch, low, middle) + mergesort(array, scratch, middle + 1, high);
        
        int tempLow = low;
        int temp = middle + 1;
        
        for (int i = low; i <= high; i++) {
            if (tempLow <= middle && (temp > high || array[tempLow] <= array[temp])) {
                scratch[i] = array[tempLow];
                tempLow++;
            } else {
                scratch[i] = array[temp];
                temp++;
                count += middle - tempLow + 1;
            }
        }
        for (int k = low; k <= high; k++) {
            array[k] = scratch[k];
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if(argv[1]!=NULL){
    	if(argc > 2){
    		cerr << "Usage: " << argv[0] << " [slow]" << endl;
    		return 1;
    	}
        string temp = "";
        for (int i = 0; i < argc-1; i++){
            temp += *argv[i];
        }
        if (temp.find("slow") == string::npos && temp.find("") == string::npos){
		    cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
		    return 1;  
        } 
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;

    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // Produce output
    if(values.empty()){
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}

    if (argc == 2) {
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    } else {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }

    return 0;
}
