/*
Sum_of_all_divisors_from_1_to_n_GFG

Given a positive integer N., The task is to find the value of    \sum_{i=1}^{i=n} F(i)  where function F(i) for the number i be defined as the sum of all divisors of ‘i‘.

    Example 1:
    Input: N = 4
    Output: 15
    Explanation:
    F(1) = 1
    F(2) = 1 + 2 = 3
    F(3) = 1 + 3 = 4
    F(4) = 1 + 2 + 4 = 7
    ans = F(1) + F(2) + F(3) + F(4) = 1 + 3 + 4 + 7 = 15

    Example 2:
    Input: N = 5
    Output: 21
    Explanation:
    F(1) = 1
    F(2) = 1 + 2 = 3
    F(3) = 1 + 3 = 4
    F(4) = 1 + 2 + 4 = 7
    F(5) = 1 + 5 = 6
    ans = F(1) + F(2) + F(3) + F(4) + F(5) = 1 + 3 + 4 + 7 + 6 = 21

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/


// Approach-1 : O(N*N) : Two for loops for finding diviser number and then adding

// Approach-2 : Just need to observe how many times 1 appearing, 2 appearing … etc in sum. So that we can just add that many times in one go!

class Solution
{
public:
    long long sumOfDivisors(int N)
    {
        // Write Your Code here
        long long sum = 0;
        
        for(int i=1; i<=N; i++)
        {
            sum += (N/i)*i;     // (N/i) represents how many times the number will appear. 
                                // The outer is 'i' is multiplied to add that number for those many times, it appears
        }
        return sum;
        
    }
};