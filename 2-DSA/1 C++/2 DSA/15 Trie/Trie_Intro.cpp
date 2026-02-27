#include<iostream>
using namespace std;


// The basic 3 features of Trie : insert, search and startswith. Most of the question will be related to these only

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
        
        // Assumption : all letter are in captial
        int index = word[0] - 'A';
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

    bool searchUtil(TrieNode* root, string word)
    {
        // Base case
        if(word.length() == 0)
        {
            return root -> isTerminal;
        }

        int index = word[0] - 'A';
        TrieNode* child;

        // present
        if(root -> children[index] != NULL)
            child = root -> children[index];
        
        else
        {
            // Absent
            return false;
        }

        // Recursion
        return searchUtil(child, word.substr(1));
    }

    bool searchWord(string word)
    {
        // T.C. of searching is O(l), where l is length of word 
        return searchUtil(root, word);
    }
    
    void removeUtil(TrieNode* root, string word)
    {
        // Base case
        if(word.length() == 0)
        {
            root -> isTerminal = false;
            return;
        }

        int index = word[0] - 'A';
        TrieNode* child;

        // present
        if(root -> children[index] != NULL)
            child = root -> children[index];
        
        else
        {
            // Absent
            return ;
        }

        // Recursion
        removeUtil(child, word.substr(1));
    }

    void removeWord(string word)
    {
        // T.C. of removal is O(l), where l is length of word 
        if( searchWord(word) == true)
        {
            removeUtil(root, word);
        }
    }

};

int main() {
    
    Trie *t = new Trie();

    t -> insertWord("ABCD");
    t -> insertWord("ARM");
    t -> insertWord("TIME");
    t -> insertWord("CODING");
    
    cout << "ABCD Present or not " << t->searchWord("ABCD") << endl;

    cout << "TIME Present or not " << t->searchWord("TIME") << endl;
    t->removeWord("TIME");
    cout << "TIME Present or not " << t->searchWord("TIME") << endl;

    return 0;
}