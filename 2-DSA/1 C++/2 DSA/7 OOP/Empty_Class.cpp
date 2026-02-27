#include<iostream>
using namespace std;

class student
{
    //Empty Class
    //Empty class have size 1 byte, to keep track of the class
};
int main()
{
    student s1;
    cout<<"Size of Empty Class : "<<sizeof(s1)<<endl;
    return 0;
}