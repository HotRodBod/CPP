/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Isabel Hughes & Rodney Wotton
 * Date        : 10/16/21
 * Description : Solves the famous water jug puzzle using breadth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <array>
#include <string>
#include <queue>

using namespace std;

struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions, State *_par) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_par} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions << " (" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void printer(State s){
	if (s.parent != nullptr)
		printer(*s.parent);
	cout << s.to_string() << endl;
}

bool waterJug(int a, int b, int c, int ga, int gb, int gc){
    queue<State> *q = new queue<State>;
    bool **visited = new bool*[a+1];
    for(int i = 0; i < a+1; i++) {
        visited[i] = new bool[b+1];
        fill(visited[i], visited[i] + (b+1), false);
    }
    q->push(State(0, 0, c, "Initial State.", nullptr));
    State* curr;	

    //while the queue is unempty
    while(!(q->empty())){
        curr = new State(q->front());
        q->pop();

        //if we havent seen the current state in the vector, mark it
        if((curr->a == ga) && (curr->b == gb) && (curr->c == gc)){
            printer(*curr);
            for(int i = 0; i < a+1; i++) {
                delete [] visited[i];
            }
            delete [] visited;
            delete q;
            return true;
        }  

        if(!visited[curr->a][curr->b]){
            visited[curr->a][curr->b] = true;
        }   
        else{
            delete curr;
        }

        int amount; 
        //Step1 C->A
        if(curr->a < a && curr->c > 0){
            if(curr->c > (a - curr->a)){
                amount = curr->a;
            }
            else{
                amount = a - curr->a;
            }
            string x = "Pour " + to_string(amount) + " gallons from C to A.";
            q->push(State(curr->a + amount, curr->b, curr->c - amount, x, curr));
        }
        //Step2 B->A
        if(curr->a < a && curr->b > 0){
            if(curr->b > (a - curr->a)){
                amount = curr->b;
            }
            else{
                amount = a - curr->a;
            }
            string x = "Pour " + to_string(amount) + " gallons from B to A.";
            q->push(State(curr->a + amount, curr->b - amount, curr->c, x, curr));
        }
        //Step3 C->B
        if(curr->b < b && curr->c > 0){
            if(curr->c > (b - curr->b)){
                amount = curr->c;
            }
            else{
                amount = b - curr->b;
            }
            string x = "Pour " + to_string(amount) + " gallons from C to B.";
            q->push(State(curr->a, curr->b + amount, curr->c - amount, x, curr));
        }
        //Step4 A->B
        if(curr->b < b && curr->a > 0){
            if(curr->a > (b - curr->b)){
                amount = curr->a;
            }
            else{
                amount = b - curr->b;
            }
            string x = "Pour " + to_string(amount) + " gallons from A to B.";
            q->push(State(curr->a - amount, curr->b + amount, curr->c, x, curr));
        }
        //Step5 B->C
        if(curr->c < c && curr->b > 0){
            if(curr->b > (c - curr->c)){
                amount = curr->b;
            }
            else{
                amount = c - curr->c;
            }
            string x = "Pour " + to_string(amount) + " gallons from B to C.";
            q->push(State(curr->a, curr->b - amount, curr->c + amount, x, curr));
        }
        //Step6 A->C
        if(curr->c < c && curr->a > 0){
            if(curr->a > (c - curr->c)){
                amount = curr->a;
            }
            else{
                amount = c - curr->c;
            }
            string x = "Pour " + to_string(amount) + " gallons from A to C.";
            q->push(State(curr->a + amount, curr->b, curr->c - amount, x, curr));
        }
    }
    //if we exit the queue, there is no solution 
    for(int i = 0; i < a+1; i++) {
        delete [] visited[i];
    }
    delete [] visited;
    delete q;
    return false;
}

int main(int argc, char * const argv[]) {
    int capA, capB, capC, goalA, goalB, goalC;
	istringstream iss;
    //incorrect number of arguments
	if(argc != 7){
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    //invalid capacities/goals
    iss.str(argv[1]);
    if(!(iss >> capA) || capA < 0){
        cout << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[2]);
    if(!(iss >> capB) || capB < 0){
        cout << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[3]);
    if(!(iss >> capC) || capC <= 0){
        cout << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[4]);
    if(!(iss >> goalA) || goalA < 0){
        cout << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[5]);
    if(!(iss >> goalB) || goalB < 0){
        cout << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[6]);
    if(!(iss >> goalC) || goalC < 0){
        cout << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
        return 1;
    }
	iss.clear();
    //goal is bigger than cap
    if(capA < goalA){
        cout << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    else if(capB < goalB){
        cout << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    else if(capC < goalC){
        cout << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    //goal addition must be equal to capC
    else if(capC != (goalA + goalB + goalC)){
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    
    if(!waterJug(capA, capB, capC, goalA, goalB, goalC)){
        cout << "No solution.";
    }
    
	return 0;
}
