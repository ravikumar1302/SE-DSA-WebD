/*
Scramble_String_InterviewBit

Given a string A, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of A = “great”:

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
 
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node “gr” and swap its two children, it produces a scrambled string “rgeat”.

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that “rgeat” is a scrambled string of “great”.

Similarly, if we continue to swap the children of nodes “eat” and “at”, it produces a scrambled string “rgtae”.

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that “rgtae” is a scrambled string of “great”.

Given two strings A and B of the same length, determine if B is a scrambled string of S.

Examples:
Input 1 :  A = "we", B = "we"
Output 1 : 1

Input 2 : A = "phqtrnilf", B = "ilthnqrpf"
Output 2 : 0

*/


// Recursive Solution
// TLE will occur

#include<bits/stdc++.h>
#include<algorithm>

bool solve(string A, string B)
{
    if(A.compare(B) == 0)   return 1;   // Equal string
    if(A.length() <= 1)     return 0;   // If only one of the string is empty
    
    int n = A.length();
    bool flag = false;  // Initially assuming not scrmabled
    
    for(int i=1; i<=n-1; i++)
    {
        bool case1 = solve(A.substr(0,i), B.substr(n-i, i)) && solve(A.substr(i,n-i), B.substr(0, n-i)) ;
        bool case2 = solve(A.substr(0,i), B.substr(0, i)) && solve(A.substr(i,n-i), B.substr(i, n-i)) ;

        if( case1 || case2)
        {
            flag = true;
            break;
        }
    }
    return flag;
}

int Solution::isScramble(const string A, const string B) {

    int a = A.length();
    int b = B.length();
    
    if(a != b) return 0;        // If size not equal
    if(a == b == 0) return 1;   // If both empty
    
    return solve(A, B);   
}


/***********************************************************************************/

// Memoization

#include<bits/stdc++.h>
#include<algorithm>

unordered_map <string, int> mp;
bool solve(string A, string B)
{
    if(A.compare(B) == 0)   return 1;   // Equal string
    if(A.length() <= 1)     return 0;   // If only one of the string is empty
    
    // Memoization code : Using Hashmap
    // We have 2 methods, matrix or hashmap
    
    string key = A;
    key.push_back(' ');
    key.append(B);
    
    if(mp.find(key) != mp.end())
        return mp[key];
    
    int n = A.length();
    bool flag = false;  // Initially assuming not scrmabled
    
    for(int i=1; i<=n-1; i++)
    {
        bool case1 = solve(A.substr(0,i), B.substr(n-i, i)) && solve(A.substr(i,n-i), B.substr(0, n-i)) ;
        bool case2 = solve(A.substr(0,i), B.substr(0, i)) && solve(A.substr(i,n-i), B.substr(i, n-i)) ;
        if( case1 || case2)
        {
            flag = true;
            break;
        }
    }
    return mp[key] = flag;
}

int Solution::isScramble(const string A, const string B) {

    int a = A.length();
    int b = B.length();
    
    if(a != b) return 0;        // If size not equal
    if(a == b == 0) return 1;   // If both empty
    
    return solve(A, B);   
}
