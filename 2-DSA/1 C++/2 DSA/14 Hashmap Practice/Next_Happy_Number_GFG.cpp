/*
Next_Happy_Number_GFG

For a given non-negative integer N, find the next smallest Happy Number. A number is called happy if it leads to 1 after a sequence of steps wherein each step number is replaced by the sum of squares of its digit that is if we start with Happy Number and keep replacing it with digits square sum, we reach 1.

    Example 1 :
    Input : N = 8
    Output : 10
    Explanation : Next happy number after 8 is 10 because 1*1 + 0*0 = 1

    Example 2:
    Input : N = 10
    Output : 13
    Explanation : after 10, 13 is a happy number because 1*1 + 3*3 = 10 1*1 + 0*0 = 1

Expected Time Complexity: O(Nlog10N)
Expected Space Complexity: O(1)
*/



// Approach-1
// Space : O(1)


class Solution{
public:

    int solve(int n)
    {
        // This is just a threshold no of iterations, within 15 ietrations digit n either will reach 0 or will have loop
        // You can take a number bigger than 10 also
        int k = 10;     
        while(n != 1 && k != 0)
        {
            int sum = 0;
            while(n != 0)   // Loop to find the squares of the digits of number
            {
                sum = sum + pow(n%10, 2);
                n = n/10;
            }
            n = sum;
            k--;
        }
        
        return n == 1;
    }
    
    int nextHappy(int N){
        
        N++;
        while(1)
        {
            int temp = solve(N);
            
            if(temp == 1)
                break;
            
            N++;
        }
        
        return N;
    }
};




// Approach-2 : For every new data, we check whether it is already in the map. If no, we insert it into the map. If yes, we detect the loop
// Space : O(N), taken by map
class Solution{
public:

    bool solve(int n)
    {
        unordered_map<int, int> mp;
        while(n != 1)
        {
            //  For every new data, we check whether it is already in the map. If no, we insert it into the map. If yes, we detect the loop
            if(mp[n] == 0)
                mp[n]++;
            else
                return false;
            
            int sum = 0;
            while(n != 0)   // Loop to find the squares of the digits of number
            {
                sum = sum + pow(n%10, 2);
                n = n/10;
            }
            n = sum;
        }
        
        return true;
    }
    
    int nextHappy(int N){
        
        N++;
        while(1)
        {
            int temp = solve(N);
            
            if(temp == 1)
                break;
            
            N++;
        }
        
        return N;
    }
};


