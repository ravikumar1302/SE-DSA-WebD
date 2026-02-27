/*
Maximize_Number_of_1_s_GFG

Given a binary array arr of size N and an integer M. Find the maximum number of consecutive 1's produced by flipping at most M 0's.
 
    Example 1:
    Input: N = 3, arr[] = {1, 0, 1}, M = 1
    Output: 3
    Explanation: Maximum subarray is of size 3 which can be made subarray of all 1 after flipping two zeros to 1.

    Example 2:
    Input: N = 11, arr[] = {1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1}, M = 2
    Output: 8
    Explanation:
    Maximum subarray is of size 8 which can be made subarray of all 1 after flipping two zeros to 1.
    
Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/


int findZeroes(int arr[], int n, int m) {
        // code here
        
        int start = 0;
        int c = 0;
        
        for(int i=0; i<n; i++)
        {
            if(arr[i] == 0)
                c++;
            if(c > m)
            {
                if(arr[start] == 0)
                    c--;
                start++;
            }
        }
        return n - start;
        
    }