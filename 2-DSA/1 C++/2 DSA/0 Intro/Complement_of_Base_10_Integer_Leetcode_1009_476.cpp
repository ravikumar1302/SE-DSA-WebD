
/*
Complement_of_Base_10_Integer_Leetcode_1009
Number Complement Leetcode_476

The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer n, return its complement.

        Example 1:
        Input: n = 5
        Output: 2
        Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

        Example 2:
        Input: n = 7
        Output: 0
        Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

        Example 3:
        Input: n = 10
        Output: 5
        Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.

Note: This question is the same as 476: https://leetcode.com/problems/number-complement/
*/

// Method-1

class Solution
{
public:
    int bitwiseComplement(int n)
    {
        int m = n;
        int mask = 0;
        if (m == 0)
            return 1;
        while (m)
        {
            mask = (mask << 1) | 1;
            m = m >> 1;
        }
        int ans = (~n) & mask;
        return ans;
    }
};

// Method-2 : Easy
// T.C.: O(log n)
// S.C.: O(log n) (string storage)
// This method fails for big input like : 2147483647. Method-1 will work in those cases

class Solution
{
public:
    int bitwiseComplement(int n)
    {
        if (n == 0)
            return 1;
        string s = "";
        int ans = 0;

        while (n)
        {
            int rem = n % 2;
            s.push_back('0' + rem);

            n = n / 2;
        }
        reverse(s.begin(), s.end()); // we have binary no now

        // takinng complement
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '0')
                s[i] = '1';
            else
                s[i] = '0';
        }

        // Convert to decimal back
        int power = 1;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            ans += (s[i] - '0') * power;
            power *= 2;
        }

        return ans;
    }
};