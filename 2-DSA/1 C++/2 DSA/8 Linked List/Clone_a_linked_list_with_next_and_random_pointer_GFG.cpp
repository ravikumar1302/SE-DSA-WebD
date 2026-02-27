/*
Clone_a_linked_list_with_next_and_random_pointer_GFG

You are given a special linked list with N nodes where each node has a next pointer pointing to its next node. You are also given M random pointers, where you will be given M number of pairs denoting two nodes a and b  i.e. a->arb = b.
Construct a copy of the given list. The copy should consist of exactly N new nodes, where each new node has its value set to the value of its corresponding original node. 
Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.
For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

    Example 1:

    Input : N = 4, M = 2, value = {1,2,3,4}, pairs = {{1,2},{2,4}}
    Output: 1
    Explanation: In this test case, there are 4 nodes in linked list.  Among these 4 nodes,  2 nodes have arbitrary pointer set, rest two nodes have arbitrary pointer as NULL. 
    Second line tells us the value of four nodes. The third line gives the information about arbitrary pointers. 
    The first node arbitrary pointer is set to node 2.  The second node arbitrary pointer is set to node 4.
*/

class Solution
{
    private:
    void insertAtTail(Node* &head, Node* &tail, int d)
    {
        Node* temp = new Node(d);
        if(head == NULL)
        {
            head = temp;
            tail = temp;
            return;
        }
        else
        {
            tail -> next = temp;
            tail = temp;
        }
    }
    
    public:
    Node *copyList(Node *head)
    {
        //Step -1: create a clone linekd list
        Node* cloneHead = NULL;
        Node* cloneTail = NULL;
        
        Node* temp = head;
        while(temp != NULL)
        {
            insertAtTail(cloneHead, cloneTail, temp -> data);
            temp = temp -> next;
        }
        
        //Step -2: Create a MAP
        unordered_map <Node*, Node*> mapping;
        Node* originalnode = head;
        Node* clonenode = cloneHead;
        while(originalnode != NULL && clonenode != NULL)
        {
            mapping[originalnode] = clonenode;
            originalnode = originalnode -> next;
            clonenode = clonenode -> next;
        }
        originalnode = head;
        clonenode = cloneHead;
        
        while(originalnode != NULL)
        {
            clonenode -> arb = mapping[originalnode -> arb];
            originalnode = originalnode -> next;
            clonenode = clonenode -> next;
        }
        return cloneHead;
    }

};
//T.C. : O(N)
//S.C. : O(N)

//Approch-2 : Without map, by changing links (T.C. : O(N) && S.C. : O(1) 

class Solution
{
    //Approch-2 : Without map, by changing links (T.C. : O(N) && S.C. : O(1) 
    
    private:
    void insertAtTail(Node* &head, Node* &tail, int d)
    {
        Node* temp = new Node(d);
        if(head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail -> next = temp;
            tail = temp;
        }
    }
    public:
    Node *copyList(Node *head)
    {
        //Step -1: create a clone list
        Node* clonehead = NULL;
        Node* clonetail = NULL;
        
        Node* temp = head;
        
        while(temp != NULL)
        {
            insertAtTail(clonehead, clonetail, temp -> data);
            temp = temp -> next;
        }
        
        //Step -2: clone node add in original list
        Node* originalnode = head;
        Node* clonenode = clonehead;
        
        while(originalnode != NULL && clonenode != NULL)
        {
            Node* next = originalnode -> next;
            originalnode -> next = clonenode;
            originalnode = next;
            
            next = clonenode -> next;
            clonenode -> next = originalnode;
            clonenode = next;
        }
        
        //Step -3: copy randompointers
         temp = head;
         while(temp != NULL)
         {
             
             if(temp -> next != NULL)
             {
                 //Using tertiary expression
                temp -> next -> arb = temp -> arb ? temp -> arb -> next : temp -> arb;
                temp = temp -> next -> next;
              }    
             
         }
        
        //Step-4: revert changes done in step 2
        originalnode = head;
        clonenode = clonehead;
        
        while(originalnode != NULL && clonenode != NULL)
        {
            originalnode -> next = clonenode -> next;
            originalnode = originalnode -> next;
            
            if(originalnode != NULL)
                clonenode -> next = originalnode -> next;
            clonenode = clonenode -> next;
        }
        
        //Step -5: return ans;
        return clonehead;
    }

};