/*
Minimum_Sum_of_Four_Digit_Number_After_Splitting_Digits_Leetcode_2160

You are given a positive integer num consisting of exactly four digits. Split num into two new integers new1 and new2 by using the digits found in num. Leading zeros are allowed in new1 and new2, and all the digits found in num must be used.

For example, given num = 2932, you have the following digits: two 2's, one 9 and one 3. Some of the possible pairs [new1, new2] are [22, 93], [23, 92], [223, 9] and [2, 329].
Return the minimum possible sum of new1 and new2.

    Example 1:
    Input: num = 2932
    Output: 52
    Explanation: Some possible pairs [new1, new2] are [29, 23], [223, 9], etc. The minimum sum can be obtained by the pair [29, 23]: 29 + 23 = 52.

    Example 2:
    Input: num = 4009
    Output: 13
    Explanation: Some possible pairs [new1, new2] are [0, 49], [490, 0], etc.  The minimum sum can be obtained by the pair [4, 9]: 4 + 9 = 13.

*/


// Approach-1 : if both numbers will be a two-digit no then the max sum can be 99+99 = 188. and for abcd, only 12 pposible ways are there to arrange
// Time, Space : O(1), as we used contant no of space (4 integers only) and constant no of operation (12 operation of min function)


class Solution {
public:
    int minimumSum(int num) {
        
        int d = num%10;
        num = num/10;
        int c = num%10;
        num = num/10;
        int b = num%10;
        num = num/10;
        int a = num%10;
        
        int mini = INT_MAX;
        
        mini = min(mini, a*10+b + c*10+d);
        mini = min(mini, a*10+b + d*10+c);
        mini = min(mini, b*10+a + c*10+d);
        mini = min(mini, b*10+a + d*10+c);
        
        mini = min(mini, a*10+c + b*10+d);
        mini = min(mini, a*10+c + d*10+b);
        mini = min(mini, c*10+a + b*10+d);
        mini = min(mini, c*10+a + d*10+b);
        
        mini = min(mini, a*10+d + b*10+c);
        mini = min(mini, a*10+d + c*10+b);
        mini = min(mini, d*10+a + b*10+c);
        mini = min(mini, d*10+a + c*10+b);
        
        return mini;
        
    }
};


// Approach-2 : store 4 digits of the 4 digit number in a array, Sort the array and return the sum of numbers
// num1 = arr[0] * 10 + arr[2];
// num2 = arr[1] * 10 + arr[3];
// sum = num1 + num2 = (arr[0] + arr[1]) * 10 + arr[2] + arr[3]
// Time - O(1)
// Space - O(1), as the size of array is taken is constant (of 4 size)

class Solution {
public:
    int minimumSum(int num) {
        
        int a[4] = {0};
        
        a[0] = num % 10;
        num /= 10;
        a[1] = num % 10;
        num /= 10;
        a[2] = num % 10;
        num /= 10;
        a[3] = num % 10;
        
        sort(a, a + 4);
        
        return ((a[0] + a[1]) * 10 + a[2] + a[3]);
    }
};