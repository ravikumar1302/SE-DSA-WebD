/*
LCM And GCD_GFG

Given two numbers A and B. The task is to find out their LCM and GCD.

    Example 1:
    Input: A = 5 , B = 10
    Output: 10 5
    Explanation: LCM of 5 and 10 is 10, while thier GCD is 5.
*/

class Solution {
  public:
  long long GCD(long long A , long long B)
  {
      if(B==0)  return A;
      else
        return GCD(B, A%B);
  }
    vector<long long> lcmAndGcd(long long A , long long B) {
        // code here
        
        long long gcd = GCD(A, B);
        long long lcm = (A*B)/gcd;
        return {lcm, gcd};
    }
};