/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Rodney Wotton
 * Version : 1.0
 * Date    : September 5, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

double sqrt(double num, double epsilon){
    double last_guess = num;
    double next_guess;
    if(num < 0){
        return numeric_limits<double>::quiet_NaN();
    }
    else if(num == 1 || num == 0){
        return num;
    }
    else{
        while (true)
        {
            next_guess = (last_guess + num/last_guess) / 2;
            if (abs(last_guess - next_guess) <= epsilon){
                break;
            }
            last_guess = next_guess;

        }
        
        return next_guess;
    }
}
int main(int argc, char* argv[]){
     double m, n;
     istringstream iss;
     cout << fixed << setprecision(8);

     if(argc == 2 || argc == 3) 
     {
         iss.str(argv[1]);
         if(!(iss >> m)){
             cerr <<"Error: Argument needs to be a double" << endl;
             return 1;
         }
         iss.clear();
         
         if(argc == 3){
             iss.str(argv[2]);
             if(!(iss >> n) || n <= 0){
                 cerr << "Error: Argument cannot be negative or equal to zero, and must be a double" << endl;
             }
       

         }
         else{
             n = 1e-7;
         }
    }
    else{
        cerr << "Error: Need either two or three arguments only" << endl;
    }
    cout << sqrt(m, n);
    return 0;
}