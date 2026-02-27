/*
Partition_Labels_Leetcode_763


You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part.
Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.
Return a list of integers representing the size of these parts.

    Example 1:
    Input: s = "ababcbacadefegdehijhklij"
    Output: [9,7,8]
    Explanation: The partition is "ababcbaca", "defegde", "hijhklij". This is a partition so that each letter appears in at most one part.
    A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.

    Example 2:
    Input: s = "eccbbbbdec"
    Output: [10]
*/

// Approach :
// Firstly to tackle this we will be needing to store the last index of each character to help us find the segment which have characters different from the other segment
// We will iterate i through the array and keep storing the end if i hits the end that means that the characters in this segment will not repeat anywhere after this
// Time: O(N)
// Space: O(1)  Constant 26 size array is used

class Solution {
public:
    vector<int> partitionLabels(string s) {
        
        unordered_map<char, int> lastIndex;
        
        // First for loop to store last position of characters
        for(int i=0; i<s.length(); i++)
            lastIndex[s[i]] = i;
        
        vector<int> ans;
        int size = 0;
        int end = 0;
        
        for(int i=0; i<s.length(); i++)
        {
            size++;
            end = max(end, lastIndex[s[i]]);
            
            if(i == end)
            {
                ans.push_back(size);
                size = 0;
            }
        }
        
        return ans;
    }
};