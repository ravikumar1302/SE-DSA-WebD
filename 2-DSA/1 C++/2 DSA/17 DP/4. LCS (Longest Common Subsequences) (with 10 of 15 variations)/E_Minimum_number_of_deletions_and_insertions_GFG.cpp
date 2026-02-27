/*
Minimum_number_of_deletions_and_insertions_GFG
OR Minimum number of deletions and insertions to transform one string into another

Given two strings str1 and str2. The task is to remove or insert the minimum number of characters from/in str1 so as to transform it into str2. 
It could be possible that the same character needs to be removed/deleted from one point of str1 and inserted to some another point.

Example 1:
Input: str1 = "heap", str2 = "pea"
Output: 3
Explanation: 2 deletions and 1 insertionp and h deleted from heap. 
Then, p is inserted at the beginning One thing to note, though p was required yet it was removed/deleted first from its position and then it is inserted to some other position. 
Thus, p contributes one to the deletion_count and one to the insertion_count.

Expected Time Complexity: O(|str1|*|str2|)
Expected Space Complexity: O(|str1|*|str2|)
*/


class Solution{
	public:
	int minOperations(string str1, string str2) 
	{ 
	    int n = str1.length();
	    int m = str2.length();
        
        int dp[n+1][m+1];
        // Initialisation
        for(int i=0; i<n+1; i++)    // 1st column
            dp[i][0] = 0;
        for(int j=0; j<m+1; j++)    // 1st row
            dp[0][j] = 0;
        
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=1; j<m+1; j++)
            {
                if(str1[i-1] == str2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
            }
        
        // dp[n][m] represents length of LCS
        int deletion = n - dp[n][m];
        int insertion = m - dp[n][m];
        
        return (insertion + deletion);  
	} 
};