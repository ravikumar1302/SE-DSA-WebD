#include<iostream>
using namespace std;
class Student {
    public :

    const int rollNumber;
    int age;

    int &x;

    Student(int r, int a) : rollNumber(r), age(a), x(this -> age) {
    }
};

// Using initialisation list we can give value to constant variable in main() function


int main() {
    Student s1(100, 23);
    cout << s1.rollNumber << " " << s1.age << " "<<s1.x<<endl;
}