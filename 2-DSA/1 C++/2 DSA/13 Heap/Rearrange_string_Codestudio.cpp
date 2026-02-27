/*
Rearrange_string_Codestudio

You are given a string “S”. Your task is to rearrange the characters of a string “S”, such that it does not contain any two adjacent characters which are the same.
If it is possible to rearrange the string “S”, then print any possible arrangement. else, print “not possible” without quotes.

For Example:
For a string  “qaacde”, This string has two same adjacent characters.
So, one possible way to rearrange the string is “qacade”. Now, this string does not have two adjacent characters that are the same. 

*/

// Approach
// Storing the frequency in map and then using this creating a max heap to store the letter in decreasing order of frequency, as the letter with maximum frequency should be dealt with care
// Using this priority queue and a temporary block to handle the letters. The last letter used will be temporarily be hold in block and deleted from heap, to use other letter and not the same in adjacent one. Then copy back.
// Do the same procedure.
// If ans size == size of string, return

#include<map>
#include<queue>
string reArrangeString(string &s)
{   
    int n = s.size();
	map<char, int> m;
    // Map to store frequency of each character
    for(char ch : s)   
        m[ch]++;
    
    // heap to store the charcter and its frequency in decreasing order
    priority_queue< pair<int, char> > pq;
    for(auto itr : m)
        pq.push(make_pair(itr.second, itr.first));
    
    string ans = "";
    pair<int, char> block = {-1, '$'};
    
    while(!pq.empty())
    {
        // Temporarily hold 1 letter and its frequency and pop it from heap
        auto temp = pq.top();
        pq.pop();
        
        ans = ans + temp.second;    // appending a letter in the ans
        temp.first--;    // decreasing the count of letter used
        
        if(block.first > 0)
            pq.push(block);
        
        block = temp;
    }
    if(n == ans.size())
        return ans;
    return "not possible";;
}
// Time : O(NlogN)
// Space : O(N)