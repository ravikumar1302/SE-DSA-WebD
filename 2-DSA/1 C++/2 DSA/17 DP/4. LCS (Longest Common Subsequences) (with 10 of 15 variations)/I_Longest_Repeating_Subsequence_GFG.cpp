/*
Longest_Repeating_Subsequence_GFG

Given string str, find the length of the longest repeating subsequence such that it can be found twice in the given string.

The two identified subsequences A and B can use the same ith character from string str if and only if that ith character has different indices in A and B. For example, A = "xax" and B = "xax" then the index of first "x" must be different in the original string for A and B.

Example 1:

Input:
str = "axxzxy"
Output: 2
Explanation:
The given array with indexes looks like
a x x z x y 
0 1 2 3 4 5

The longest subsequence is "xx". 
It appears twice as explained below.

subsequence A
x x
0 1  <-- index of subsequence A
------
1 2  <-- index of str 


subsequence B
x x
0 1  <-- index of subsequence B
------
2 4  <-- index of str 

We are able to use character 'x' (at index 2 in str) in both subsequences as it appears on index 1 in subsequence A and index 0 in subsequence B.

Expected Time Complexity: O(n2)
Expected Space Complexity: O(n2)

*/

// Approach : just add one connditon in if loop of choice diagram

class Solution {
	public:
		int LongestRepeatingSubsequence(string str){
		    
		int n = str.length();
        
        int dp[n+1][n+1];
        // Initialisation
        for(int i=0; i<n+1; i++)    // 1st column
            dp[i][0] = 0;
        for(int j=0; j<n+1; j++)    // 1st row
            dp[0][j] = 0;
        
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=1; j<n+1; j++)
            {
                if(str[i-1] == str[j-1] && i !=j)   // We can also copy str and do the same for 2 equal string
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
            }
        
        return dp[n][n]; 
		    
		}
};