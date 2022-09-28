/*******************************************************************************
 * Name        : shortestpath.cpp
 * Author      : Rodney Wotton & Isabel Hughes
 * Date        : December 5, 2021
 * Description : Shortest Paths with Floyd's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <iomanip> 
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const long INF = numeric_limits<long>::max();

void display_table(long** const matrix, const string &label, int num_vertices, const bool use_letters = false) { 
    cout << label << endl; 
    long max_val = 0; 
    for (int i = 0; i < num_vertices; i++) { 
        for (int j = 0; j < num_vertices; j++) { 
            long cell = matrix[i][j]; 
            if (cell < INF && cell > max_val) { 
                max_val = matrix[i][j]; 
            } 
        } 
    } 
 
    int max_cell_width = to_string(max(static_cast<long>(num_vertices - 1), max_val)).length();
    cout << ' '; 
    for (int j = 0; j < num_vertices; j++) { 
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A'); 
    } 
    cout << endl; 
    for (int i = 0; i < num_vertices; i++) { 
        cout << static_cast<char>(i + 'A'); 
        for (int j = 0; j < num_vertices; j++) { 
            cout << " " << setw(max_cell_width); 
            if (matrix[i][j] == INF) { 
                cout << "-"; 
            } else if (use_letters) { 
                cout << static_cast<char>(matrix[i][j] + 'A'); 
            } else { 
                cout << matrix[i][j]; 
            } 
        } 
        cout << endl; 
    } 
    cout << endl; 
} 

vector<char> backtrack(int i, int j, long** inv){
    vector<char> path;

    if(inv[i][j] == INF){
        path.push_back('A' + j);
        if(('A' + j) != ('A' + i)){
            path.push_back('A' + i);
        }
        return path;
    }
    else{
        path = backtrack(i, inv[i][j], inv);
        vector<char> opath = backtrack(inv[i][j], j, inv);
        opath.insert(opath.end(), path.begin()+1, path.end());
        return opath;
    }  
}

void floyds_algorithm(long** matrix, long numvert){
    long** path_length = matrix;
    long** inv = new long*[numvert];

    for(int i = 0; i < numvert; i++){
        inv[i] = new long[numvert];
        for(int j = 0; j < numvert; j++){
            inv[i][j] = INF;
        }
    }

    for(int k = 0; k < numvert; k++){
        for(int i = 0; i < numvert; i++){
            for(int j = 0; j < numvert; j++){
                if (path_length[i][k] != INF && path_length[k][j] != INF && path_length[i][k] + path_length[k][j] < path_length[i][j]){
                    inv[i][j] = k;
                    path_length[i][j] = path_length[i][k] + path_length[k][j];
                }
                
            }
        }
    }

    display_table(path_length, "Path lengths:", numvert, false);
    display_table(inv, "Intermediate vertices:", numvert, true);

    for(int i = 0; i < numvert; i++){
        char begin = 'A' + i;
        for(int j = 0; j < numvert; j++){
            char end = 'A' + j;

            if(begin == end){
                cout << begin << " -> " << end << ", distance: 0, path: " << begin << endl;
            }
            else{
                cout << begin << " -> " << end << ", distance: ";
                if(path_length[i][j] != INF){
                    cout << path_length[i][j] << ", path: " << begin; 
                    vector<char> path = backtrack(i, j, inv); 
                    reverse(path.begin(), path.end());
                    for(size_t k = 1; k < path.size(); k++){
                        cout << " -> " << path.at(k);
                    }
                    cout << endl;
                }
                else{
                    cout << "infinity, path: none" << endl;
                }
            }
        }
    }
    
    for(int i = 0; i < numvert; i++) {
        delete [] path_length[i];
        delete [] inv[i];
    }
    delete [] path_length;
    delete [] inv;
}

int main(int argc, char *argv[]){
    //if number of arguments is incorrect
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    //loading file into vector<string> for each line
    vector<string> filez;
    ifstream input_file(argv[1]);
    if(input_file.is_open()){
        string line;
        unsigned int line_number = 1;
        while (getline(input_file, line)) {
            ++line_number;
            filez.push_back(line);
        }
        input_file.close();
    }
    else{
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    istringstream iss;
    int k;
    int linecount = 1;
    vector<vector<string>> totals;
    for(string a : filez){
        if(linecount == 1){
            iss.str(a);
            if(!(iss >> k) || k > 26 || k < 1){
                cerr << "Error: Invalid number of vertices '" << a << "' on line 1.";
                return 1;
            }
            k += 64;
            iss.clear();
        }
        else{
            if(a.length()< 5){
                cerr << "Error: Invalid edge data '" << a << "' on line " << linecount << ".";
                return 1;
            }
            size_t pos = 0;
            vector<string> words;

            while((pos = a.find(" ")) != string::npos){
                words.push_back(a.substr(0, pos));
                a.erase(0, pos+1);
            } 
            words.push_back(a);
            totals.push_back(words);
            int count = 0;
            string ktran;
            ktran = (char) k;
            for(string b : words){
                if(count == 0){
                    if(b > ktran || b < "A"){
                        cerr << "Error: Starting vertex '" << b << "' on line " << linecount << " is not among valid values A-"<< ktran << "." << endl;
                        return 1;
                    }
                }
                else if(count == 1){
                    if(b > ktran || b < "A"){
                        cerr << "Error: Ending vertex '" << b << "' on line " << linecount << " is not among valid values A-" << ktran << "." << endl;
                        return 1;
                    }
                }
                else{
                    for (char const &c : b) {
                        if(isdigit(c) == 0 && c != '-'){
                            cerr << "Error: Invalid edge weight '" << b <<"' on line " << linecount << "."  << endl; 
                            return 1;
                        }
                        else if(stoi(b) < 1){
                            cerr << "Error: Invalid edge weight '" << b <<"' on line " << linecount << "."  << endl; 
                            return 1;
                        }
                    }
                }
                count++;
            }
        }
        linecount++;
    }
    k -= 64;
    //sets distance matrix to its 0 diagonal
    long** distmat = new long*[k];
    for(int i = 0; i < k; i++){
        distmat[i] = new long[k];
        for(int j = 0; j < k; j++){
            if(i != j){
                distmat[i][j] = INF;
            }
            else{
                distmat[i][j] = 0;
            }
        }
    }
    
    for(vector<string> x : totals){
        distmat[int(x.at(0)[0])-65][int(x.at(1)[0])-65] = stoi(x.at(2));
    }
    
    display_table(distmat, "Distance matrix:", k, false);
    floyds_algorithm(distmat, k);
    return 0;
}