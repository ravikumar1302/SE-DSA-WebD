/*
Count_primes_Leetcode_204
Given an integer n, return the number of prime numbers that are strictly less than n.

    Example 1:
    Input: n = 10
    Output: 4
    Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

This Method is Known as "SIEVE OF ERATOSTHENES"
*/

class Solution {
public:
    int countPrimes(int n) {
        
        // Using Sieve of Eratosthenes
        
        vector<bool> prime(n+1,true);       // Note : Size is n+1
        int count =0;
        
        prime[0]=prime[1]=false;
        for(int i=2;i<n;i++)
        {
            if(prime[i])
            {
                count++;
                for(int j=2*i;j<n;j=j+i)
                    prime[j]=false;
            }
        }
        return count;
    }
};