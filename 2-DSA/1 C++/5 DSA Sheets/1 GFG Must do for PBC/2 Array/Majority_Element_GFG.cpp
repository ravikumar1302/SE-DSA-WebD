/*
Majority_Element_GFG
Majority_Element_Leetcode_169


Given an array A of N elements. Find the majority element in the array. A majority element in an array A of size N is an element that appears more than N/2 times in the array.
 
    Example 1:
    Input: N = 3, A[] = {1,2,3} 
    Output: -1
    Explanation: Since, each element in {1,2,3} appears only once so there is no majority element.

    Example 2:
    Input: N = 5, A[] = {3,1,3,3,2} 
    Output: 3
    Explanation: Since, 3 is present more than N/2 times, so it is the majority element.

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(1).
*/

// Approcah-1 : O(nlogn) time and O(1) space : Sort the array, as major element is MORE than N/2 time, it will be present at index N/2 or ans = nums[N/2]

// Apprach-2 : Linear Time and O(N) Space : Use hashmap to store the frequency of each element and then return the ans with most frequenccy


// Approach-3 : Best Solution : Linear time and O(1) Space 
                // Use 2 variables to count the frequency of elementts

class Solution{
  public:
     // Function to find majority element in the array
    // a: input array
    // size: size of input array
    int majorityElement(int a[], int size)
    {
        
        int ans = a[0], cnt = 1;
        for(int i=1; i<size; i++)
        {
            if(a[i] == ans)
                cnt++;
            else if(cnt == 0)
            {
                cnt++;
                ans = a[i];
            }
            else        // means a[i] != ans and cnt != 0
                cnt--;
        }
        
        // Now we have potential ans, let's verify it
        int temp = 0;
        for(int i=0; i<size; i++)
            if(a[i] == ans)
                temp++;
        
        if(temp <= size/2)
            return -1;

        return ans;
        
        
    }
};