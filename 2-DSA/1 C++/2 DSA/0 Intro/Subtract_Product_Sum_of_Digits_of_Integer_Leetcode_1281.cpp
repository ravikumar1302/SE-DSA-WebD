/*
Subtract_Product_Sum_of_Digits_of_Integer_Leetcode_1281.cpp

Given an integer number n, return the difference between the product of its digits and the sum of its digits.

    Example 1:
    Input: n = 234
    Output: 15
    Explanation:
    Product of digits = 2 * 3 * 4 = 24
    Sum of digits = 2 + 3 + 4 = 9
    Result = 24 - 9 = 15

*/

class Solution
{
public:
    int subtractProductAndSum(int n)
    {
        int pro = 1, sum = 0, result = 0;

        int temp = n;
        while (temp)
        {
            int rem = temp % 10;

            pro = pro * rem;
            sum = sum + rem;

            temp = temp / 10;
        }

        result = pro - sum;
        return result;
    }
};
