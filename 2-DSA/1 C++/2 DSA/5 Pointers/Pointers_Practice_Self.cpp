#include<iostream>
using namespace std;
int main()
{
    /*
    //Nice Question-1
    char st[] = "ABCD";
    for(int i = 0; st[i] != ‘\0’; i++) 
        cout << st[i] << *(st)+i << *(i+st) << i[st];
    
    //Nice Question-2
      float arr[5] = {12.5, 10.0, 13.5, 90.5, 0.5};
      float *ptr1 = &arr[0];
      float *ptr2 = ptr1 + 3;
      cout<<*ptr2<<" ";
      cout<< ptr2 - ptr1;
   
    //Printing Error: Below Code don't give any output
    int *ptr = 0;
    int a = 10;
    *ptr = a;
    cout << *ptr << endl;
    
    //Double Pointer
    int i=5;
    int *ptr=&i;
    int **ptr1=&ptr;
    cout<<"*ptr "<<ptr<<endl;
    cout<<"**ptr1 "<<ptr1;

    
    //Character Array pointer
    char temp='z';
    char *p=&temp;
    cout<<p<<endl;  //after "z" it prints element till it find a null character
    
    int arr[]={0,1,2,3,4};
    for(int i=0;i<5;i++)
        cout<<i[arr]<<endl; // it is same as arr[i]
    
    //Just Playing with Pointers Part-1
    int num=6;
    int *p=&num;

    int *q = p;
    cout << p <<" - " << q << endl;
    cout << *p <<" - " << *q << endl;
    cout << &p <<" - " << &q << endl;

    int i = 3;
    int *t = &i;
    //cout <<  (*t)++ << endl;
    *t = *t +1;
    cout << *t << endl;
    cout << " before t " << t << endl;
    t = t + 1;
    cout << " after t " << t << endl;
    cout << " value at t after increrement " << *t << endl;
    */
    //Just Playing with Pointers Part-2
    int n=5;
    int *ptr = &n;
    cout<<sizeof(&ptr)<<endl;

    cout<<n<<endl;
    cout<<&n<<endl;
    cout<<ptr<<endl;
    cout<<*ptr<<endl;
    cout<<&(*ptr)<<endl;
    cout<<*(&(*ptr))<<endl;
    
    return 0;
}