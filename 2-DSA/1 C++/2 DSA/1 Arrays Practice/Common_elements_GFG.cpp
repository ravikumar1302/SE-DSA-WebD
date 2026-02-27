/*
Common_elements_GFG
Common Elements In Three Sorted Arrays_Codestudio

Given three arrays sorted in increasing order. Find the elements that are common in all three arrays.
Note: can you take care of the duplicates without using any additional Data Structure?

Example 1:
Input:
n1 = 6; A = {1, 5, 10, 20, 40, 80}
n2 = 5; B = {6, 7, 20, 80, 100}
n3 = 8; C = {3, 4, 15, 20, 30, 70, 80, 120}
Output: 20 80
Explanation: 20 and 80 are the only common elements in A, B and C.

Expected Time Complexity: O(n1 + n2 + n3)
Expected Auxiliary Space: O(n1 + n2 + n3)
*/


// Space : O(1) excluding space taken by ans
// Time : O(N1 + N2 + N3)


class Solution
{
    public:    
       vector <int> commonElements (int A[], int B[], int C[], int n1, int n2, int n3)
        {
            vector<int> ans;
            int i=0, j=0, k=0;
            
            while(i<n1 && j<n2 && k<n3)
            {
                if(A[i] == B[j] && B[j] == C[k])
                {
                    ans.push_back(A[i]);
                    i++;
                    j++;
                    k++;
                }
                else if(A[i] < B[j])    // if array1 elements are smaller than the array2
                    i++;
                else if(B[j] < C[k])    // if array2 elements are smaller than the array3
                    j++;
                else                    // //if array3 elements are smaller than the array1 and array2
                    k++;
                
                // For duplicay of elements in the same array
                while(A[i-1] == A[i])   i++;
                while(B[j-1] == B[j])   j++;
                while(C[k-1] == C[k])   k++;
            }
            
            return ans;
        }

};