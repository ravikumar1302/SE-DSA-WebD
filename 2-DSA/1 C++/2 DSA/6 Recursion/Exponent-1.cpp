
// Exponent_1


#include<iostream>
using namespace std;

int pow(int a , int b, int pro, int count)
{
    if(count == b)
        return pro;
    pro=pro*a;
    count++;
    return pow(a,b,pro,count);
}
int main()
{
    int pro=1, count =0;
    int a=4, b=5;
    int power = pow(a,b,pro,count);
    cout<<power;
    return 0;
}