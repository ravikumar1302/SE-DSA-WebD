#include<iostream>
using namespace std;

class A {
private:
    static int i;
    int a;
    char b;

public:
    A()
    {
        a = 0;
        b = '#';
    }
    A(int aa, char bb)
    {
        a = aa;
        b = bb;
    }
    int get_int()
    {
        cout << a << endl;
        return a;
    }
    char get_char()
    {
        cout << b << endl;
        return b;
    }
};

int main()
{
    A a1;   //object of class A
    cout<<"Size of class A (expected 4) "<<sizeof(a1)<<endl;
    cout<<"The extra 4 byte is due to padding"<<endl;

    return 0;
}