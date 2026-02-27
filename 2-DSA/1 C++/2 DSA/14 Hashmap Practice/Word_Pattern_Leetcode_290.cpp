/*
Word_Pattern_Leetcode_290

Given a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s.

Example 1:
Input: pattern = "abba", s = "dog cat cat dog"
Output: true

Example 2:
Input: pattern = "abba", s = "dog cat cat fish"
Output: false

Example 3:
Input: pattern = "aaaa", s = "dog cat cat dog"
Output: false
*/


class Solution {
public:
    bool wordPattern(string pattern, string s) {
        
        string word;
        vector<string> words;
        
        // Storing individual words
        stringstream iss(s);    // iss is just a variiable
        while(iss >> word)
            words.push_back(word);
        
        if(pattern.size() != words.size())
            return false;
        
        unordered_map<char, string> mp;
        set<string> st;
        
        for(int i=0; i<pattern.size(); i++)
        {
            if( mp.find(pattern[i]) != mp.end())    // Element present in map
            {
                if(mp[pattern[i]] != words[i])
                    return false;
            }
            else
            {
                if(st.count(words[i]) > 0)
					return false;
				
				mp[pattern[i]] = words[i];
				st.insert(words[i]);
            }
        }
        
        return true;
    }
};


/*
Why Use Set ?? : his test case pattern = "abc" and s = "dog cat cat". AND count() is an inbuilt function in set. It returns 1 if the given element is present and returns 0 if the element is not present.

Other way to store words :

    vector<string> v;
		int i = 0;
		string temp = "";
		while(i < s.size()){
			if(s[i] == ' '){
				v.push_back(temp);
				temp = "";
			}
			else{
				temp += s[i];
			}
			i++;
		}
	v.push_back(temp);
*/