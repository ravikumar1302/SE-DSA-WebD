/*
Implement_a_phone_directory_Codestudio

You are given a list/array of strings which denotes the contacts that exist in your phone directory. The search query on a string ‘str’ which is a query string displays all the contacts which are present in the given directory with the prefix as ‘str’. One special property of the search function is that when a user searches for a contact from the contact list then suggestions (contacts with prefix as the string entered so for) are shown after the user enters each character.
Note :
If no suggestions are found, return an empty 2D array.

    Sample Input 1 :
    2
    5
    cod coding codding code coly
    coding
    2
    ninjas coding
    ninja
    Sample Output 1 :
    cod coding codding code coly
    cod coding codding code coly
    cod coding codding code coly
    coding
    coding
    coding
    ninjas
    ninjas
    ninjas
    ninjas
    ninjas
    Explanation To Sample Input 1 :
    In the first test case, 
    The suggestions for “c” is {“cod”, “coding”, “codding”, “code”, “coly”}.
    The suggestions for “co” is {“cod”, “coding”, “codding”, “code”, “coly”}.
    The suggestions for “cod” is {“cod”, “coding”, “codding”, “code”, “coly”}.
    The suggestion for “codi” is {“coding”}.
    The suggestion for “codin” is {“coding”}.
    The suggestion for “coding” is {“coding”}.

    In the second test case, 
    The suggestion for “n” is {“ninjas”}.
    The suggestion for “ni” is {“ninjas”}.
    The suggestion for “nin” is {“ninjas”}.
    The suggestion for “ninj” is {“ninjas”}.
    The suggestion for “ninja” is {“ninjas”}.

*/

class TrieNode
{
    public:
    char data;
    TrieNode* children[26];
    bool isTerminal;

    TrieNode(char ch)
    {
        data = ch;
        for(int i=0; i<26; i++)
            children[i] = NULL;
        isTerminal = false;
    }
};

class Trie
{
    public:
    TrieNode* root;

    Trie()
    {
        root = new TrieNode('\0');
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

    void printsuggestion(TrieNode* curr, vector<string> &temp, string prefix)
    {
        // Base case
        if(curr -> isTerminal)
        {
            temp.push_back(prefix);
            // The return was removed from here because we can have nodes after terminal also
        }
        
        for(char ch ='a'; ch<='z'; ch++)
        {
            TrieNode* next = curr -> children[ch - 'a'];
            
            if(next != NULL)
            {
                prefix.push_back(ch);
                printsuggestion(next, temp, prefix);
                prefix.pop_back();
            }
        }
    }
    
    vector<vector<string>> getSuggestions(string str)
    {
        TrieNode* prev = root;
        vector<vector<string>> output;
        string prefix = "";
        
        for(int i=0; i<str.length(); i++)
        {
            char lastch = str[i];
            
            prefix.push_back(lastch);
            
            // Check for lastch
            TrieNode* curr = prev -> children[lastch - 'a'];
            
            // If not found
            if(curr == NULL)
                break;
            
            // If found
            vector<string> temp;
            printsuggestion(curr, temp, prefix);
            
            output.push_back(temp);
            temp.clear();
            prev = curr;
        }
        return output;
    }
    
};

vector<vector<string>> phoneDirectory(vector<string>&contactList, string &queryStr)
{
    // Creation of trie
    Trie *t = new Trie();
    
    // Insertion of all elements in TRIE
    for(int i=0; i<contactList.size(); i++)
    {
        string str = contactList[i];
        t->insertWord(str);
        
    }
    // Return ans
    return t->getSuggestions(queryStr);
}

// If avg string is M and there are N strings in contactList
// T.C. : O(N*M*M)
// S.C. : O(M*N)