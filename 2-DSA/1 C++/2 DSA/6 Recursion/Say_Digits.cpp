/*
Say_Digits
If input is given, n=421, print : four two one
*/

#include<iostream>
using namespace std;

void saydigit(int n, string arr[])
{
    if(n==0)    //base case
        return ;

    int digit=n%10;
    n=n/10;

    saydigit(n,arr);

    cout<<arr[digit]<<" ";
}
int main()
{
    int n;
    cin>>n;
    string arr[10]={"zero","one","two","three","four","five","six","seven","eight","nine"};
    saydigit(n , arr);
    return 0;
}