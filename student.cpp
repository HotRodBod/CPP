#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

int main(){
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;

    do{
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while(gpa < 0 || gpa > 4){
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    }while(repeat == 'Y' || repeat == 'y');

    cout << endl << "All students:" << endl;
    print_students(students);

    cout << endl << "Failing students:";
    vector<Student> fail = find_failing_students(students);
    if(fail.empty()){
        cout << " None" <<endl;
    }
    else{
        cout << endl;
        print_students(fail);
    }
    return 0;
}
