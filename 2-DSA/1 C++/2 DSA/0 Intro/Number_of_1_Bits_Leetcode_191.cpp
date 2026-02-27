/*
Number_of_1_Bits_Leetcode_191

Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).

    Example 1:
    Input: n = 11
    Output: 3
    Explanation: The input binary string 1011 has a total of three set bits.

    Example 2:
    Input: n = 128
    Output: 1
    Explanation: The input binary string 10000000 has a total of one set bit.

    Example 3:
    Input: n = 2147483645
    Output: 30
    Explanation:The input binary string 1111111111111111111111111111101 has a total of thirty set bits.

    Constraints:

    1 <= n <= 231 - 1

Follow up: If this function is called many times, how would you optimize it?
*/

class Solution
{
public:
    int hammingWeight(int n)
    {
        string str = "";

        int temp = n;
        while (temp)
        {
            int rem = temp % 2;
            str += (rem + '0');

            temp = temp / 2;
        }

        reverse(str.begin(), str.end());

        int ans = 0;
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '1')
                ans++;
        }

        return ans;
    }
};

// Simple & Correct Solution (Bitwise)

int hammingWeight(int n)
{
    int count = 0;

    while (n > 0)
    {
        count += (n & 1); // check last bit
        n >>= 1;          // right shift
    }

    return count;
}

// Even Better (Optimized – Brian Kernighan’s Algorithm)

int hammingWeight(int n)
{
    int count = 0;

    while (n)
    {
        n = n & (n - 1); // removes the lowest set bit
        count++;
    }

    return count;
}