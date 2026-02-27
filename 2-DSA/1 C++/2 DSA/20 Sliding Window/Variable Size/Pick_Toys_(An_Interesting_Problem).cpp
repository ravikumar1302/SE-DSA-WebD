/*
Pick_Toys_(An_Interesting_Problem)

Problem Link : No Where, it was an interview problem

John is at a toy store help him pick maximum number of toys. He can only select in a continuous manner and he can select only two types of toys.

    Example:
    Input: 1
    abaccab
*/

// Similar Leetcode problem : Fruit_Into_Baskets_Leetcode_904


#include <bits/stdc++.h>
using namespace std;

int maxToys(string &toys, int k)
{
    unordered_map<char,int> mp;     
    int n=toys.length(), ans=0;

    int i=0, j=0;                 

    while(j<n)
    {
        mp[toys[j]]++;

        //conditions met
        if((int)mp.size() <= k)
            ans = max(ans, j-i+1);
        
        //max different types of toys condition violated
        else
        {
            while((int)mp.size() > k)
            {
                mp[toys[i]]--;
                if(mp[toys[i]] == 0) 
                    mp.erase(toys[i]);

                i++;
            }
        }

        j++;
    }

    return ans;
}

// Time complexity - O(n) 
// Space complexity - O(k)

int main()
{
    string toys = "abbcba";
    int k=2;

    cout << "Max toys that can be bought -> " << maxToys(toys,k) << endl;   //ans is bbcb

    return 0;
}