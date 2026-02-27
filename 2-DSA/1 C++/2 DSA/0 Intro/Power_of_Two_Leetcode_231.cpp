/*
Power_of_Two_Leetcode_231

Given an integer n, return true if it is a power of two. Otherwise, return false.

An integer n is a power of two, if there exists an integer x such that n == 2x.

    Example 1:
    Input: n = 1
    Output: true
    Explanation: 20 = 1

    Example 2:
    Input: n = 16
    Output: true
    Explanation: 24 = 16

    Example 3:
    Input: n = 3
    Output: false

Constraints: -231 <= n <= 231 - 1

Follow up: Could you solve it without loops/recursion?
*/

bool isPowerOfTwo(int n)
{
    int flag = 0;
    for (int i = 0; i < 31; i++)
    {
        int power = pow(2, i);
        if (power == n)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        return true;
    else
        return false;
}

// Best Approach (Bit Manipulation)

bool isPowerOfTwo(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

/*
Idea : A power of two in binary has exactly one 1 bit.

Why it works:
1. n has one 1
2. n - 1 flips that 1 to 0 and turns lower bits to 1
3. ANDing them removes all bits → 0
*/