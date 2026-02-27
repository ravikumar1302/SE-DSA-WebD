/*
Remove_duplicate_elements_from_sorted_Array_GFG
Remove Duplicates from Sorted Array Leetcode_26

Given a sorted array A[] of size N, delete all the duplicated elements from A[]. Modify the array such that if there are X distinct elements in it then the first X positions of the array should be filled with them in increasing order and return the number of distinct elements in the array.
Note:
1. Don't use set or HashMap to solve the problem.
2. You must return the number of distinct elements(X) in the array, the generated output will print all the elements of the modified array from index 0 to X-1.

    Example 1:
    Input: N = 5, Array = {2, 2, 2, 2, 2}
    Output: {2}
    Explanation: After removing all the duplicates only one instance of 2 will remain.

    Example 2:
    Input: N = 3, Array = {1, 2, 2}
    Output: {1, 2}

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/

int remove_duplicate(int a[],int n){
        
        int ans = 1;    //as first element is not considered duplicate, index1 is the first available place
        
        for(int i=1; i<n; i++)
        {
            if(a[i] != a[i-1])
                a[ans++] = a[i];    //bring all non duplicates to front
        }
        return ans;
        
    }