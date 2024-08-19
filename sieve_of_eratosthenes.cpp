/*******************************************************************************
 * Name        : sieve_of_eratosthenes.cpp
 * Description : Sieve of Eratosthenes
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    int c = -1;
    const int max_prime_width = num_digits(max_prime_), 
        primes_per_row = 80 / (max_prime_width + 1);
    
    cout << endl << "Number of primes found: " << count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    
    for (int i = 2; i <= limit_; i++) {
        if (max_prime_ <= 101) {
            if (is_prime_[i]) {
                if (i == max_prime_) {
                    cout << i;
                }
                else {
                    cout << i << " ";
                }
            }
        }
        else if (is_prime_[i]) {
            c++;

            if (c == primes_per_row) {
                cout << endl;
                c = 0;
            }
            if (c == 0) {
                cout << setw(max_prime_width) << i;
            }
            else {
                cout << setw(max_prime_width + 1) << i;
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // Count the number of primes found
    int a = 0;
    for (int i = 2; i < limit_ + 1; i++) {
        if (is_prime_[i]) {
            a += 1;
        }
    }
    return a;
}

void PrimesSieve::sieve() {
    // Sieve algorithm
    memset(is_prime_, true, limit_ + 1);

    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i]) {
            for (int j = i * i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }

    for (int j = 2; j <= limit_; j++) {
        if (is_prime_[j]) {
            max_prime_ = j;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // Determine how many digits are in num
    int a = num;
    int num_digits = 0;

    while (a > 0) {
        num_digits++;
        a /= 10;
    }
    
    return num_digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    istringstream iss(limit_str);

    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve filter(limit);
    filter.display_primes();

    return 0;
}
