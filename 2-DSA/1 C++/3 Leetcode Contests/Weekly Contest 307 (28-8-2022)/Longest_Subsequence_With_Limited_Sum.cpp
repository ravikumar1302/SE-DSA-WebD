/*
Longest_Subsequence_With_Limited_Sum

You are given an integer array nums of length n, and an integer array queries of length m.

Return an array answer of length m where answer[i] is the maximum size of a subsequence that you can take from nums such that the sum of its elements is less than or equal to queries[i].

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: nums = [4,5,2,1], queries = [3,10,21]
Output: [2,3,4]
Explanation: We answer the queries as follows:
- The subsequence [2,1] has a sum less than or equal to 3. It can be proven that 2 is the maximum size of such a subsequence, so answer[0] = 2.
- The subsequence [4,5,1] has a sum less than or equal to 10. It can be proven that 3 is the maximum size of such a subsequence, so answer[1] = 3.
- The subsequence [4,5,2,1] has a sum less than or equal to 21. It can be proven that 4 is the maximum size of such a subsequence, so answer[2] = 4.
Example 2:

Input: nums = [2,3,4,5], queries = [1]
Output: [0]
Explanation: The empty subsequence is the only subsequence that has a sum less than or equal to 1, so answer[0] = 0.

Constraints:

n == nums.length
m == queries.length
1 <= n, m <= 1000
1 <= nums[i], queries[i] <= 106

*/

class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        
        int n = nums.size();
        int m = queries.size();
        
        sort(nums.begin(), nums.end());
        vector<int> prefix(n);
        prefix[0] = nums[0];
        for(int i=1; i<n; i++)
            prefix[i] = prefix[i-1] + nums[i];
        
        vector<int> ans;
        //vector<int> :: iterator it;
        for(int i=0; i<m; i++)
        {
            int value = queries[i];
            
            if(prefix[0] > value)
                ans.push_back(0);
            else
            {
               for(int j=0; j<n; j++)
                {
                    if(prefix[j] == value)
                    {
                        ans.push_back(j+1);
                        break;
                    }
                    else if(prefix[j] > value )
                    {
                        ans.push_back(j);
                        break;
                    }
                   else if(j==n-1)
                   {
                       ans.push_back(j+1);
                       break;
                   }
                } 
            }
                
            
            //it = lower_bound(prefix.begin(), prefix.end(), value);
            //if(prefix[it - prefix.begin()] == value)
            //ans.push_back(it - prefix.begin() + 1 );
        }
        return ans;
    }
};