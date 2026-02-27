/*
Rotate_Array_GFG

Given an unsorted array arr[] of size N. Rotate the array to the left (counter-clockwise direction) by D steps, where D is a positive integer. 

    Example 1:
    Input: N = 5, D = 2, arr[] = {1,2,3,4,5}
    Output: 3 4 5 1 2
    Explanation: 1 2 3 4 5  when rotated by 2 elements, it becomes 3 4 5 1 2.

    Example 2:
    Input: N = 10, D = 3, arr[] = {2,4,6,8,10,12,14,16,18,20}
    Output: 8 10 12 14 16 18 20 2 4 6
    Explanation: 2 4 6 8 10 12 14 16 18 20 when rotated by 3 elements, it becomes 8 10 12 14 16 18 20 2 4 6.
 
Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/


// Method-1 : Time-O(N) and Space-O(1)

class Solution{
    public:
    
    //Function to rotate an array by d elements in counter-clockwise direction. 
    void rotateArr(int arr[], int d, int n){
        
        
        // Edge case (very imp) : if d > n
        d = d%n;
        
        // Try this method on Pen-Paper
        reverse (arr + 0, arr + d);
        reverse (arr + d, arr + n);
        reverse (arr + 0, arr + n);
    }
};



// Method-2 : Time-O(N) and Space-O(d)

class Solution{
    public:
    
    //Function to rotate an array by d elements in counter-clockwise direction. 
    void rotateArr(int arr[], int d, int n){
        
        int m[d];
        d=d%n;
        
        int count=0;
        for(int i=0;i<d;i++)    // Copying first 'd' elements in another array
            m[i]=arr[i];
            
        for(int i=0;i<n;i++)
        {
            if(i<n-d)       // moving remaining 'n-d' elements to start
                arr[i]=arr[i+d];

            else        // Moving copied elemets to the original array
            {
                arr[i]=m[count];
                count++;
            }
        }
    }
};

        