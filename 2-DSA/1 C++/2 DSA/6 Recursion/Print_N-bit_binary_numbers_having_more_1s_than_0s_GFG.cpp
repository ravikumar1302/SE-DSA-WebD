/*
Print_N-bit_binary_numbers_having_more_1s_than_0s_GFG

Given a positive integer N, the task is to find all the N bit binary numbers having more than or equal 1’s than 0’s for any prefix of the number.

    Example 1:

    Input:  N = 2
    Output: 11 10
    Explanation: 11 and 10 have more than or equal 1's than 0's

Expected Time Complexity: O(|2N|)
Expected Auxiliary Space: O(2N)

*/

class Solution{
public:	

    void solve(int one, int zero, vector<string> &ans, string output, int N)
    {
        // Base case
        if(N == 0)  {
            ans.push_back(output);
            return;
        }
        
        // Processing and Recursive call
        string op1 = output;
        op1.push_back('1');
        solve(one +1, zero, ans, op1, N-1);
        
        if(one > zero)  {
            string op2 = output;
            op2.push_back('0');
            solve(one, zero+1, ans, op2, N-1);           
        }
        return;
    }
    
	vector<string> NBitBinary(int N)
	{
	    vector<string> ans;
	    string output = "";
	    
	    int zero = 0;
	    int one = 0;
	    
	    solve(one, zero, ans, output, N);

	    return ans;
	}
};
