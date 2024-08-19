/*******************************************************************************
 * Name        : unique_letters.cpp
 * Description : Determining uniqueness of chars with int as bit vector.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    return (s.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == string::npos);
}

// Returns true if all letters in string are unique
bool all_unique_letters(const string &s) {
    unsigned int bitset = 0;

    for (int i = s.length(); i >= 0; --i){
        int temp = 1 << (s[i]);
        
        if (bitset & temp) {
            return false ;
        }
        bitset |= temp;
    }
    return true;
}

int main(int argc, char * const argv[]) {
    if (argc == 1) {
        cout << "Usage: ./unique <string>" << endl;
    } else if (argc > 2) {
        cout << "Usage: ./unique <string>" << endl;
    } else if (!is_all_lowercase(argv[1])) {
        cout<< "Error: String must contain only lowercase letters."  << endl;
    } else if (!all_unique_letters(argv[1])) {
        cout<< "Duplicate letters found."  << endl;
    } else {
        cout<< "All letters are unique."  << endl;
    }
}
