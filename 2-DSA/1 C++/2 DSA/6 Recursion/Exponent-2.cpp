/*
Exponent_2

This is very optimized technique.
2 to the power 10, was earlier going to have 1024 iterations, but now only 11

*/
#include<iostream>
using namespace std;

int pow(int a , int b)
{
    if(b==0)
        return 1;
    if(b==1)
        return a;
    int ans = pow(a , b/2);  // Recursive call
    if(b%2==0)
        return ans*ans;
    else
        return a*ans*ans;
    


}
int main()
{
    int a=2, b=10;
    int power = pow(a,b);
    cout<<power;
    return 0;
}