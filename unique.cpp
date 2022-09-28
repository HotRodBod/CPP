/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Rodney Wotton
 * Date        : 9/25
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(int i = 0; i < s.length(); i++){
        if (!islower(s[i])){
            return false;
        }
    }
    return true;
    // returns true if all characters in string are lowercase
    // iterates through the string and checks each character
}
bool all_unique_letters(const string &s) {
    unsigned int vector = 0;
    unsigned int setter;
    for(int i = 0; i < s.length(); i++){
        setter = 1 << (s[i] - 'a');
        if((vector & setter) == setter){
            return false;
        }
        vector |= setter;


    }
    return true;
    // iterates through the string with the for loop
    // finds the setter using bitwise and compares it to vector to see if the letter is unique


}

int main(int argc, char * const argv[]) {
    if (argc != 2){
        cout << "Usage: ./unique <string>" << endl;
    }
    else{
        if (is_all_lowercase(argv[1])){
            if(all_unique_letters(argv[1])){
                cout << "All letters are unique." << endl;
            }
            else{
                cout << "Duplicate letters found." << endl;
            }
        }
        else{
            cout << "Error: String must contain only lowercase letters." << endl;
        }
    }

    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
}
