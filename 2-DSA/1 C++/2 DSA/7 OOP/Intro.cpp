#include<iostream>
using namespace std;

class student
{
    public:
    int rollno;
    int grade;
    
};
int main()
{

    //Static Allocation
    student s0;

    //Dynamic Allocation
    student *s1 = new student;     //Like int *a = new int
    
    cout<<(*s1).rollno<<endl;
    cout<<(*s1).grade<<endl;

    cout<<s1->rollno<<endl;
    cout<<s1->grade<<endl;
    return 0;
}