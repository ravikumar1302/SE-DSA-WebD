#include<iostream>
using namespace std;

//Static variable are called using class name, not object. So, they don't consume memory with every object.

class Student {
    public :

    int rollNumber;
    static int totalStudents;

    Student() {
        totalStudents++;
    }
};

int Student::totalStudents = 20;    //Initializing static variable

int main() {
    Student s1, s2, s3, s4;
    cout << Student :: totalStudents;   //Way to access the static variable
}