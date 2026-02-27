/*
Palindrome_Number_Leetcode_9

Given an integer x, return true if x is palindrome integer.
An integer is a palindrome when it reads the same backward as forward.
For example, 121 is a palindrome while 123 is not.
 
    Example 1:
    Input: x = 121
    Output: true
    Explanation: 121 reads as 121 from left to right and from right to left.

    Example 2:
    Input: x = -121
    Output: false
    Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Follow up: Could you solve it without converting the integer to a string?
*/


class Solution {
public:
    bool isPalindrome(int x) {
        
        if(x < 0)   // negative no are not palindrome
            return false;
        
        vector<int> n;
        while(x)
        {
            int rem = x%10;
            n.push_back(rem);
            x = x/10;
        }
        
        for(int i=0; i<n.size(); i++)
        {
            if(n[i] != n[n.size() - i - 1])
                return false;
        }
        
        return true;
    }
};

// Approach : Store the digits of number in a vector and then check for palindrome
// Time and Space : O(N)




// Approach-2

class Solution
{
	public:
		string is_palindrome(int n)
		{
		    // Code here.
		    string word = to_string(n);
		    int i=0; 
		    int j = word.size()-1;
		    
		    while(i <= j)
		    {
		        if(word[i] != word[j])
		            return "No";
		        i++;
		        j--;
		    }
		    
		    return "Yes";
		}
};