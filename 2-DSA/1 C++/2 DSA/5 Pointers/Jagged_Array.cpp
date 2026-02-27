//Using array and a pointer (Static Jagged Array)

#include <iostream>
using namespace std;  
int main()
{
  
    int row0[4] = { 1, 2, 3, 4 };
    int row1[2] = { 5, 6 };
  
    int* jagged[2] = { row0, row1 };
  
    // Array to hold the size of each row
    int Size[2] = { 4, 2 }, k = 0;
  
    // To display elements of Jagged array
    for (int i = 0; i < 2; i++) {
  
        // pointer to hold the address of the row
        int* ptr = jagged[i];
  
        for (int j = 0; j < Size[k]; j++) {
            cout<<*ptr<<" ";
  
            // move the pointer to the
            // next element in the row
            ptr++;
        }
  
        cout<<endl;
        k++;
  
        // move the pointer to the next row
        jagged[i]++;
    }
  
    return 0;
}


/*
//Using an array of pointer (Dynamic Jagged Array)
// 2 Rows
    int* jagged[2];
  
    // Allocate memory for elements in row 0
    jagged[0] = malloc(sizeof(int) * 1);
  
    // Allocate memory for elements in row 1
    jagged[1] = malloc(sizeof(int) * 3);
  
    // Array to hold the size of each row
    int Size[2] = { 1, 3 }, k = 0, number = 100;
  
    // User enters the numbers
    for (int i = 0; i < 2; i++) {
  
        int* p = jagged[i];
  
        for (int j = 0; j < Size[k]; j++) {
            *p = number++;
  
            // move the pointer
            p++;
        }
        k++;
    }
  
    k = 0;
  
    // Display elements in Jagged array
    for (int i = 0; i < 2; i++) {
  
        int* p = jagged[i];
        for (int j = 0; j < Size[k]; j++) {
  
            cout<<*p<<" ";
            // move the pointer to the next element
            p++;
        }
        cout<<endl;
        k++;
        // move the pointer to the next row
        jagged[i]++;
    }
  
    return 0;
*/