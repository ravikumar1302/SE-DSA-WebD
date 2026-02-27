/*
Ugly_Number_Leetcode_263

An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
Given an integer n, return true if n is an ugly number.

    Example 1:
    Input: n = 6
    Output: true
    Explanation: 6 = 2 × 3

    Example 2:
    Input: n = 1
    Output: true
    Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.

    Example 3:
    Input: n = 14
    Output: false
    Explanation: 14 is not ugly since it includes the prime factor 7.

*/

// Time : O(logN), In each division performed in the while loop n is getting reduced by at least half, Input will become n n/2 n/4 n/8...1 so the runtime is O(logn)

class Solution {
public:
    bool isUgly(int n) {
        
        while(n%5 ==0 && n) 
            n/=5;
        while(n%4 ==0 && n)     // It will reduce the no of iterations for 2
            n/=4;     
        while(n%3 ==0 && n) 
            n/=3; 
        while(n % 2 == 0 && n) 
            n/=2;
        
        // Return ans
        if(n == 1)    // Means it has only those prime factos which are limited to 2, 3, 5
            return true;
        else
            return false;
    }
};