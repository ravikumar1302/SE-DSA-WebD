#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    map <int, int> un;
    int a,b,n;
    cout<<"Enter no of test cases : ";
    cin>>n;
    for(int i=0; i<n; i++)    
    {   
        cin>>a>>b;
        un[a] = b;
    }
    
    cout <<endl<< "Map is : "<<endl;
    map<int,int> :: iterator itr;
    for(itr=un.begin(); itr!=un.end(); itr++)
    {
        cout<<itr->first<<" "<<itr->second<<endl;
    }
    return 1;
}