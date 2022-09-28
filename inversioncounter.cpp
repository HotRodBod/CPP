/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Rodney Wotton
 * Version     : 1.0
 * Date        : 10/30/21
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long n=0;
    for(int i = 0; i<length - 1; ++i){
    	for (int j = i+1; j < length; ++j){
    		if(array[i] > array[j]) {
    	        n++; 
            }
    	}
    }
    return n;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
    long inversions = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    if(low == high) {
	    return 0;
	}
    const int middle = static_cast<unsigned int>(low + (high - low) / 2);
    long count = mergesort(array, scratch, low, middle);
    count += mergesort(array, scratch, middle + 1, high);
    int l = low;
    int r = middle+1;
    int j = low;
    for(int i = low; i <= high; i++) {
        scratch[i] = array[i];
    }
    while(l <= middle && r <= high) {
        if(scratch[l] <= scratch[r]) {
            array[j++] = scratch[l++];
        }
        else {
            count += middle - l + 1;
            array[j++] = scratch[r++];
        }
    }
    while (l <= middle)
        array[j++] = scratch[l++];
    while (r <= high)
        array[j++] = scratch[r++];
    return count;
	    
}

int main(int argc, char *argv[]) {
    int slow = 0;
    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]";
        return 1;
    }
    if((argv[1] != NULL) && (strcmp("slow",argv[1]) == 0)){
        slow = 1;
    }
    else if(argv[1] != NULL){
        cerr << "Error: Unrecognized option '" << argv[1] << "'.";
        return 1;
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

   if(index == 0){
        cerr << "Error: Sequence of integers not received." << endl;
    }
    else{
        if(slow == 1){
            cout << "Number of inversions: " << count_inversions_slow(&values[0], index);
        }
        else{
            cout << "Number of inversions: " << count_inversions_fast(&values[0], index);
        }
    }

    return 0;
}