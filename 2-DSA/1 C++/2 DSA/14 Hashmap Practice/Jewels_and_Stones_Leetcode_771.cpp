/*
Jewels_and_Stones_Leetcode_771

You're given strings jewels representing the types of stones that are jewels, and stones representing the stones you have. Each character in stones is a type of stone you have. You want to know how many of the stones you have are also jewels.

Letters are case sensitive, so "a" is considered a different type of stone from "A".

    Example 1:

    Input: jewels = "aA", stones = "aAAbbbb"
    Output: 3
*/

class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        
        // Approach : enter the stones data in an hasmap and then while traversing jewels find how many matches
        unordered_map<char,int> mp;
        for(int i=0; i<stones.size(); i++)
            mp[stones[i]]++;
        
        int cnt = 0;
        for(int i=0; i<jewels.size(); i++)
            if(mp.find(jewels[i]) != mp.end())
                cnt += mp[jewels[i]];
        
        return cnt;
        
    }
};

// Time : O(N)
// Space : O(N)