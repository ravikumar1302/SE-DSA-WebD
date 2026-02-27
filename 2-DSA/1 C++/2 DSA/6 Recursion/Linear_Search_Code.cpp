
// Linear_Search_Practice


#include<iostream>
using namespace std;

bool linearsearch(int arr[], int size, int key)
{
    if(size == 0)   //base case-1, element not found
        return false;
    if(arr[0]==key) //base case-2, element found
        return true;
    
    else
        return linearsearch(arr+1,size-1,key);
}
int main()
{
    int arr[]={1,2,5,7,10};
    int size=5;
    int key=11;

    bool ans =linearsearch(arr,size,key);
       if(ans)
        cout<<"Element is present"<<endl;
    else
        cout<<"Element is absent";
    
    return 0;
}