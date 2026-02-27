/*
Boolean_Parenthesization_GFG
OR Evaluate Expression to True Boolean Parenthesization Recursive

Given a boolean expression S of length N with following symbols.
Symbols
    'T' ---> true
    'F' ---> false
and following operators filled between symbols
Operators
    &   ---> boolean AND
    |   ---> boolean OR
    ^   ---> boolean XOR
Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true.

    Example 1:
    Input: N = 7, S = T|T&F^T
    Output: 4
    Explaination: The expression evaluates  to true in 4 ways ((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T) and (T|((T&F)^T)).

Expected Time Complexity: O(N3)
Expected Auxiliary Space: O(N2)
*/


// Approach : Like Palnidrome Partioning, we will put bracket/ make partition before each operator to see expresssion value

// Recursive Solution
// TLE will ocuur

class Solution{
public:
    
    int solve(string S, int i, int j, bool isTrue)
    {
        // Step-1 : Find i and j
        // Step-2 : Base case
        if(i > j)
            return false;
        if(i == j)
        {
            if(isTrue == true)
                return S[i] == 'T';
            else
                return S[i] == 'F';
        }
        
        // Step- 3 : K-loop Scheme
        int ans = 0;
        for(int k = i+1; k <= j-1; k=k+2)
        {
            int lt = solve(S, i, k-1, true);
            int lf = solve(S, i, k-1, false);
            int rt = solve(S, k+1, j, true);
            int rf = solve(S, k+1, j, false);
            
            // Step-4 : Find ans from temp ans
            
            if(S[k] == '&')
            {
                if(isTrue == true)
                    ans = ans + lt*rt;
                else
                    ans = ans + (lt*rf + lf*rt + lf*rf);
            }
            if(S[k] == '|')
            {
                if(isTrue == true)
                    ans = ans + (lt*rt + lt*rf + lf*rt);
                else
                    ans = ans + lf*rf;
            }
            if(S[k] == '^')
            {
                if(isTrue == true)
                    ans = ans + (lt*rf + lf*rt);
                else
                    ans = ans + ( lt*rt  + lf*rf);
            }
        }
        
        return ans;
    }
    
    int countWays(int N, string S){
        int i = 0;
        int j = N-1;
        bool isTrue = true;
        
        return solve(S, i, j, isTrue);
    }
};


/************************************************************************************/

// Memoization 

class Solution{
public:
    unordered_map <string, int> mp;
    int solve(string S, int i, int j, bool isTrue)
    {
        // Step-1 : Find i and j
        // Step-2 : Base case
        if(i > j)
            return false;
        if(i == j)
        {
            if(isTrue == true)
                return S[i] == 'T';
            else
                return S[i] == 'F';
        }
        
        // Memoization code : Using Hashmap
        // We have 2 methods, 3-D matrix or hashmap
        
        string temp = to_string(i);
        temp.push_back(' ');
        temp.append(to_string(j));
        temp.push_back(' ');
        temp.append(to_string(isTrue));
        
        if(mp.find(temp) != mp.end())
            return mp[temp];
        
        // Step- 3 : K-loop Scheme
        int ans = 0;
        for(int k = i+1; k <= j-1; k=k+2)
        {
            int lt = solve(S, i, k-1, true);
            int lf = solve(S, i, k-1, false);
            int rt = solve(S, k+1, j, true);
            int rf = solve(S, k+1, j, false);
            
            // Step-4 : Find ans from temp ans
            
            if(S[k] == '&')
            {
                if(isTrue == true)
                    ans = ans + lt*rt;
                else
                    ans = ans + (lt*rf + lf*rt + lf*rf);
            }
            if(S[k] == '|')
            {
                if(isTrue == true)
                    ans = ans + (lt*rt + lt*rf + lf*rt);
                else
                    ans = ans + lf*rf;
            }
            if(S[k] == '^')
            {
                if(isTrue == true)
                    ans = ans + (lt*rf + lf*rt);
                else
                    ans = ans + ( lt*rt  + lf*rf);
            }
        }
        
        return mp[temp] = ans%1003;     // returns number of possible ways modulo 1003 (Given in task of GFG Porblem statement)
    }
    
    int countWays(int N, string S){
        int i = 0;
        int j = N-1;
        bool isTrue = true;
        
        return solve(S, i, j, isTrue);
    }
};


/************************************************************************************/

//  Code from Discussion Panel of GFG
// Explained well in comments

//Aditya Verma Solution

int solve(string S, int i, int j, bool isTrue, unordered_map <string, int> &mp)
{
   //now the base case
   if(i > j)
   {
       //if empty string
       return 0;
       //there are 0 ways to make empty string true/false.
   }
   
   if(i == j)
   {
       //now i and j will only occur at T or F so..
       //i == j means only single character.
       
       //agar isTrue hai that is banana hai true aur milta hai true toh 1 way otherwise 0 ways.
       if(isTrue)
       {
           if(S[i] == 'T')
           {
               return 1;
           }
           else{
               return 0;
           }
       }
       else{
           if(S[i] == 'F')
           {
               return 1;
           }
           else{
               return 0;
           }
       }
   }
   
   //yeh abhi base cases ka kaam khatam hua.
   
   //here, we are making the key store in the map.
   string temp = to_string(i);
   temp.push_back(' ');
   //string.append function is used to append to add to the calling string.
   temp.append(to_string(j));
   temp.push_back(' ');
   temp.append(to_string(isTrue));
   
   //agr map mei mil jata hai answer toh wohi return kr do.
   if(mp.find(temp) != mp.end())
   {
       return mp[temp];
   }
   
   int ans = 0;
   
   //ab loop mei dekhei toh k i+1 se start hokr j-1 tak jayega as it has to stay on operators.
   //k+=2 hoga as operators alternatively hi honge and unnke ek agey aur ek peeche partition hoga.
   for(int k = i+1; k<j; k+=2)
   {
       //left expression k true honne k ways
       int lt = solve(S, i, k-1, true, mp);
       
       //left expression k false honne k ways
       int lf = solve(S, i, k-1, false, mp);
       
       //right expression k true honne k ways
       int rt = solve(S, k+1, j, true, mp);
       
       //right expression k false honne k ways
       int rf = solve(S, k+1, j, false, mp);
       
       if(S[k] == '&')
       {
           //agar mera current expression & ka hai toh....
           if(isTrue)
           {
               //current expression ko true krne k ways
               ans += lt*rt;
           }
           else{
               //current expression ko false krne k ways
               ans += lf*rt + lt*rf + lf*rf;
           }
       }
       else if(S[k] == '|')
       {
           //agar current expression | ya or hua toh.
           if(isTrue)
           {
               //current expression ko true krne k ways
               ans += lt*rt + lf*rt + lt*rf;
           }
           else{
               //current expression ko false krne k ways
               ans += lf*rf;
           }
       }
       else if(S[k] == '^')
       {
           //agar current expression xor hua toh
           if(isTrue)
           {
               //current expression ko true krne k ways
               ans += lf*rt + lt*rf;
           }
           else{
               //current expression ko false krne k ways
               ans += lf*rf + lt*rt;
           }
       }
   }
   
   //jo bhi answer aa jata hai ussey return kr do.
   return mp[temp] = ans % 1003;
}
