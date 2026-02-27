/*
Check_palindrome 
Using palindrome we will check whether string is palindrome or not
*/

#include<iostream>
using namespace std;

bool palindrome(string str, int i, int j)
{
    if(i>j)
        return true;
    if(str[i]!=str[j])
        return false;
    else 
        return palindrome(str,i+1,j-1);
}
int main()
{
    string str= "nitin";
    bool ispal = palindrome(str,0, str.length()-1);
    if(ispal)
        cout<<"Palindrome"<<endl;
    else
        cout<<"Not Palindrome"<<endl;
    return 0;
}