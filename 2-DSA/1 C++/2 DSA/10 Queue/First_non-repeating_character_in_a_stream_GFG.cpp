/*
First_non-repeating_character_in_a_stream_GFG

Given an input stream of A of n characters consisting only of lower case alphabets. The task is to find the first non repeating character, each time a character is inserted to the stream. If there is no such character then append '#' to the answer.
 
    Example 1:

    Input: A = "aabc"
    Output: "a#bb"
    Explanation: For every character first non repeating character is as follow-
    "a" - first non-repeating character is 'a'
    "aa" - no non-repeating character so '#'
    "aab" - first non-repeating character is 'b'
    "aabc" - first non-repeating character is 'b'
	
Expected Time Complexity: O(26 * n)
Expected Space Complexity: O(26)
*/

class Solution {
	public:
		string FirstNonRepeating(string A){
		    queue<char> q;
		    string ans ="";
		    unordered_map<char, int> count;
		   
		    for(int i=0; i<A.length(); i++)
		    {
		        char ch = A[i];
		        
		        //Increase it's count
		        count[ch]++;
		        
		        //push it in queue
		        q.push(ch);
		        
		        while(!q.empty())
		        {
		            //Repeating character
		            if(count[q.front()] > 1)
		                q.pop();
		            else    //non repeating character
		                {
		                    ans.push_back(q.front());
		                    break;
		                }
		        }
		        if(q.empty())
		            ans.push_back('#');
		    }
		    return ans;
		}
};