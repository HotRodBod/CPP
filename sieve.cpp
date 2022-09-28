/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Rodney Wotton
 * Date        : Sept. 13 2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

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
    for(int i=2; i<=limit; i++){
        is_prime_[i] = true;
    }
    sieve();
    num_primes_ = count_num_primes();
    for (int i = limit; i>= 2; i--){
        if (is_prime_[i]){
            max_prime_ = i;
            break;
        }
    }

}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_); 
    const int primes_per_row = 80 / (max_prime_width + 1);
    int count = 1, c = 1;
    if(num_primes_ > primes_per_row){
        for(int i=2; i<=limit_; i++){
            if (count <= primes_per_row){
                if (is_prime_[i]){
                    count += 1;
                    cout <<  setw(max_prime_width) << i;
                    if( i != max_prime_ && count <= primes_per_row){
                        cout << " ";
                    }
                }
            }
            else {
                count = 1;
                cout << endl;
            }
        }
    }
    else{
        for(int i=2; i<=limit_; i++){
            if (is_prime_[i]){
                cout << i;
            }
            if(is_prime_[i+1]){
                c += 1;
                cout << " ";
            }
            else{
                c = 1;
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
   int count = 0;
    for(int i=2; i<=limit_; i++){

        if(is_prime_[i]){
        count += 1;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    for(int i=2; i<=sqrt(limit_); i++){
        if(is_prime_[i]){
            for(int j=i*i; j<=limit_; j+=i) {
                is_prime_[j] = false;
            }
        }
    }

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 1;
    while(num / 10 != 0){
        count++;
        num = num/10;

    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output
    
    PrimesSieve num1(limit);
    cout << "\nNumber of primes found: " << num1.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    num1.display_primes();


    return 0;
}
