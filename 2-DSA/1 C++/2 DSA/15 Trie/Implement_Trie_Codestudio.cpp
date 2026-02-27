/*
Implement_Trie_Codestudio

Implement Trie Data Structure to support these operations:
insert(word) - To insert a string "word" in Trie
search(word) - To check if string "word" is present in Trie or not.
startsWith(word) - To check if there is any string in the Trie that starts with the given prefix string "word".


Three type of queries denote these operations:
Type 1: To insert a string "word" in Trie.
1 word

Type 2: To check if the string "word" is present in Trie or not.
2 word

Type 3: To check if there is any string in the Trie that starts with the given prefix string "word".
3 word


    Sample Input 1 :
    5
    1 hello
    1 help
    2 help
    3 hel
    2 hel 
    Sample Output 1 :
    true
    true
    false
    Explanation To Sample Input 1 :
    Query 1: "hello" is inserted
    Query 2: "help" is inserted
    Query 3: "true" is printed as "help" is present
    Query 4: "true" is printed as "hello" and "help" is present having the prefix "hel"
    Query 5: "false" is printed as "hel" is not present
    
*/

/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);
 */

// Contains 2 Methods : one by striver and other by love babbar

// Method-1 : by Striver

/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);
 */
struct Node {    // Class can also be used instead of struct, just define private and public section
    Node* links[26];
    bool flag = false;
    bool containsKey(char ch)  {  //checks if the reference trie is present or not
        return (links[ch - 'a'] != NULL);
    }
    
    void put(char ch, Node* node)    {    //creating reference trie
        links[ch - 'a'] = node;
    }
    
    Node* get(char ch)    {    //to get the next node for traversal
        return links[ch - 'a'];
    }
    
    bool setEnd()    {    //setting flag to true at the end of the word
        flag = true;
    }
    bool isEnd()    {    //checking if the word is completed or not
        return flag;
    }
};

class Trie {
private : 
    Node* root;
public:

    /** Initialize your data structure here. */
    Trie() {
        root = new Node(); 
    }

    /** Inserts a word into the trie. */
    // Time : O(len)
    void insert(string word) {
        Node* node = root;
        for(int i=0; i<word.length(); i++)
        {
            if(!node -> containsKey(word[i]))    // does not contain
                node -> put(word[i], new Node());
            
            // moves to the new refrence trie
            node = node->get(word[i]);
        }
        node-> setEnd();
    }

    /** Returns if the word is in the trie. */
    // Time : O(len)
    bool search(string word) {
        Node* node = root;
        for(int i=0; i<word.length(); i++)
        {
            if(!node -> containsKey(word[i]))
                return false;
            
            node = node->get(word[i]);
        }
        return node -> isEnd();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    // Time : O(len)
    bool startsWith(string prefix) {
        Node* node = root;
        for(int i=0; i<prefix.length(); i++)
        {
            if(!node -> containsKey(prefix[i]))
                return false;
            
            node = node->get(prefix[i]);
        }
        return true;
    }
};



/********************************************************************************************************/

// Method-2 : by Love Babbar

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

class Trie {

public:
    TrieNode* root;
    /** Initialize your data structure here. */
    Trie() {
    root = new TrieNode('\0');
    }

    
    
    
    /** Inserts a word into the trie. */
    void insertUtil(TrieNode* root, string word)
    {
        // Base case
        if(word.length() == 0)
        {
            root -> isTerminal = true;
            return;
        }
        
        // Assumption : all letter are in captial
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
    
    void insert(string word) {
        insertUtil(root, word);
    }

    
    
    
    
    /* Returns if the word is in the trie. */
    bool searchUtil(TrieNode* root, string word)
    {
        // Base case
        if(word.length() == 0)
        {
            return root -> isTerminal;
        }

        int index = word[0] - 'a';
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
    
    bool search(string word) {
        return searchUtil(root, word);
    }

    
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool prefixUtil(TrieNode* root, string word)
    {
        // Base case
        if(word.length() == 0)
        {
            return true;
        }

        int index = word[0] - 'a';
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
        return prefixUtil(child, word.substr(1));
    }
    
    bool startsWith(string prefix) {
        return prefixUtil(root, prefix);
    }
};