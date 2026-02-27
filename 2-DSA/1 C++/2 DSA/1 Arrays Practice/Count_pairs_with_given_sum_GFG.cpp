/*
Count_pairs_with_given_sum_GFG

Given an array of N integers, and an integer K, find the number of pairs of elements in the array whose sum is equal to K.

Example 1:
Input : N = 4, K = 6, arr[] = {1, 5, 7, 1}
Output : 2
Explanation : arr[0] + arr[1] = 1 + 5 = 6 and arr[1] + arr[3] = 5 + 1 = 6.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(N)
*/


// Naive Approach : O(N^2)

class Solution{   
public:
    
    int getPairsCount(int arr[], int n, int k) {
        
        int ans = 0;
        for(int i=0; i<n-1; i++)
        {
            int a = arr[i];
            for(int j=i+1; j<n; j++)
                if(a + arr[j] == k)
                    ans++;
        }
        
        return ans;
    }
};


// Optimized Approach
// This also giving TLE

class Solution{   
public:
    // Optimized Approach : sort and then 2 pointer approach
    // Time : O(N) + O(NlogN)
    
    int getPairsCount(int arr[], int n, int k) {
        
        int count = 0;
        // Step-1
        sort(arr, arr+n);
        
        // Step-2 : 2 pointer approach
        int start = 0;
        int end = n-1;
        
        while(start < end)
        {
            if(arr[start] + arr[end] == k)
                {
                    count++;
                    start++;
                    //end--;
                }
            else if(arr[start] + arr[end] < k)
                start++;
            else
                end--;
        }
        
        return count;
    }
};

// Optimized : Using Hashmap
// Time : O(N) and space : O(N)

class Solution{   
public:
    // Optimized : Using Hashmap
    // Time : O(N) and space : O(N)
    
    int getPairsCount(int arr[], int n, int k) {
        
        int count = 0;
        unordered_map<int,int> mp;
        
        for(int i=0; i<n; i++)
        {
            if(mp[k-arr[i]])    // if value present
                count += mp[k-arr[i]];
            
            mp[arr[i]]++;   // frequency of each data will be increased
        }
        return count;
    }
};