/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Rodney Wotton
 * Date        : 10/2/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways; 
    vector<int> way;

// if the number of stairs is less than or equal to zero, it will add the vector, way, into the vector of vector ints, ways.
    if (num_stairs <= 0){
        ways.push_back(way);
    }
    // for each number of climable stairs
    for(int i=1; i<4; i++){
        // if statement checks to see if it is possible to move up i stairs
        if (num_stairs >= i){
            vector<vector<int>> result = get_ways(num_stairs - i); 
            //adds i to result
            for(int j=0; j < result.size(); j++){
                result.at(j).push_back(i);
            }
            //adds the contents of result to ways 
            for(int j=0; j < result.size(); j++){
                ways.push_back(result.at(j));
            }
        }
    }
    return ways;

}
// counts the number of digits for setting the width
int count_digit(int number){
    if (number < 10){
        return 1;
    }
    else{
        return 1 + count_digit(number / 10);
    }
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int count = 1;
    //iterates through the vector ints of ways
    for (vector<int> x : ways){
        cout << right << setw(count_digit(ways.size())) << count << ". [";
        count++;
        //iterates through the int elements of x
        for(int a = x.size()-1; a >= 0; a--){
            cout << x.at(a);
            // determines when to print a comma
            if(a != 0){
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    istringstream iss;
    int compare;

    // if the amount of arguments is not two
    if (argc != 2){
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    else{

        iss.str(argv[1]);
        // if the argument isnt an int or is not a psoitive integer
        if (!(iss >> compare) || compare < 1){
            cout << "Error: Number of stairs must be a positive integer." << endl;
            return 1;
        }
        else{
            iss.clear();
            //if the inputed stairs to climb is one
            if(compare == 1){
                cout << "1 way to climb 1 stair." << endl;
            
            }
            else{
                cout << get_ways(compare).size() << " ways to climb " << compare << " stairs." << endl;

            }
            display_ways(get_ways(compare));
        }
    } 
    return 0;
}
