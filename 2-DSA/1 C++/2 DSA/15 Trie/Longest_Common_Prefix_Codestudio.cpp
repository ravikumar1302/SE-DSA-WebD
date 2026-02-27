/*
Longest_Common_Prefix_Codestudio

You are given an array ‘ARR’ consisting of ‘N’ strings. Your task is to find the longest common prefix among all these strings. If there is no common prefix, you have to return an empty string.
A prefix of a string can be defined as a substring obtained after removing some or all characters from the end of the string.

    For Example:
    Consider ARR = [“coding”, ”codezen”, ”codingninja”, ”coders”]
The longest common prefix among all the given strings is “cod” as it is present as a prefix in all strings. Hence, the answer is “cod”.

*/

string longestCommonPrefix(vector<string> &arr, int n)
{
    string ans ="";
    
    // For traversing all character of first string
    for(int i =0; i<arr[0].length();i++)
    {
        char ch = arr[0][i];
        bool match = true;
        
        // For comparing 'ch' with rest of the strings
        for(int j = 1; j<n; j++)
        {
            // Not match : brreak
            if(arr[j].size() < i || ch != arr[j][i])
            {
                match = false;
                break;
            }
        }
        
        if(match == false)
            break;
        else
            ans.push_back(ch);
    }
    return ans;
}

// T.C. : O(M*N) // M is length of first string
// S.C. : O(M)  // if considering space used for storing ans, else it's O(1)



/**********************************************************************************************/

/* 
    Approach 2 : Using Trie
    Step 1 : Insert all strings into the trie
                Now make this trie in yiur notbook and observe that if some node has child-count == 1, then it is common, add it in ans,
                Add till there is only one child
    Step 2 : Return ans
*/

// T.C. : O(M*N) // M is length of first string
// S.C. : O(M*N) 

// Approach -2 Using TRIE

// Giving TLE in last case

class TrieNode
{
    public:
    char data;
    TrieNode* children[26];
    int childCount;
    bool isTerminal;

    TrieNode(char ch)
    {
        data = ch;
        for(int i=0; i<26; i++)
            children[i] = NULL;
        isTerminal = false;
        childCount = 0;
    }
};

class Trie
{
    public:
    TrieNode* root;

    Trie(char ch)
    {
        root = new TrieNode(ch);
    }
    
    void insertUtil(TrieNode* root, string word)
    {
        // Base case
        if(word.length() == 0)
        {
            root -> isTerminal = true;
            return;
        }
        
        // Assumption : all letter are in small
        int index = word[0] - 'a';
        TrieNode* child;

        // Present
        if(root -> children[index] != NULL)
            child = root -> children[index];
        
        else
        {
            // Absent
            child = new TrieNode(word[0]);
            root -> childCount++;
            root -> children[index] = child;
        }
        
        // Recursion
        insertUtil(child, word.substr(1));  // Passing remaning string, except the first letter
    }

    void insertWord(string word)    
    {
        // T.C. of insertion is O(l), where l is length of word 
        insertUtil(root, word);
    }
    
    void lcp(string str, string &ans)
    {
        for(int i=0; i<str.length(); i++)
        {
            char ch = str[i];
            if(root -> childCount == 1)
            {
                ans.push_back(ch);
                // Go ahead
                int index = ch -'a';
                root = root->children[index];
            }
            else
                break;
            
            if(root -> isTerminal)
                break;
                
        }
    }
};

string longestCommonPrefix(vector<string> &arr, int n)
{
    Trie *t = new Trie('\0');
    
    // insert all strigs into trie
    for(int i=0; i<n; i++)
        t->insertWord(arr[i]);
    
    string first = arr[0];
    string ans = "";
    
    t->lcp(first, ans);
    
    return ans;
}


