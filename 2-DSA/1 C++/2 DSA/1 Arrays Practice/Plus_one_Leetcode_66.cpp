/*
Plus_one_Leetcode_66
Plus one_GFG

You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.

    Example 1:
    Input: digits = [1,2,3]
    Output: [1,2,4]
    Explanation: The array represents the integer 123. Incrementing by one gives 123 + 1 = 124. Thus, the result should be [1,2,4].
*/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        
        digits.back() += 1;
        for (auto i = digits.size() - 1; i > 0; i--) 
        {
            if (digits.at(i) == 10) 
            {
                digits.at(i) = 0;
                digits.at(i - 1) += 1;
            }
        }
        if (digits.front() == 10) 
        {
            digits.insert(digits.begin(), 1);
            digits.at(1) = 0;
        }
        return digits;
    }   
};



class Solution {
  public:
    vector<int> increment(vector<int> arr ,int N) {
        
        vector<int> ans = arr;
        reverse(ans.begin(), ans.end());
        
        int carry = 1;
        for(int i=0; i<N; i++)
        {
            if(ans[i] == 9 && carry == 1)
            {
                carry = 1;
                ans[i] = 0;
            }
            else
            {
                ans[i] = ans[i] + carry;
                carry = 0;
            }
        }
        if(carry ==1)
            ans.push_back(1);
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};