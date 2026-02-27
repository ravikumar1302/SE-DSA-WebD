/*
Merge_k_sorted_lists_Codestudio

Given 'K' sorted linked lists, each list is sorted in increasing order. You need to merge all these lists into one single sorted list. 
You need to return the head of the final linked list.

    Sample Input 1:
    2
    3
    4 6 8 -1
    2 5 7 -1
    1 9 -1
    2
    2 6 -1
    -5 7 -1
    Sample Output 1:
    1 2 4 5 6 7 8 9 -1
    -5 2 6 7 -1
    Explanation For Input 1:
    For first test case:
    First list is: 4 -> 6 -> 8 -> NULL
    Second list is: 2 -> 5 -> 7 -> NULL
    Third list is: 1 -> 9 -> NULL
    The final list would be: 1 -> 2 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> NULL

    For second test case:
    First list is: 2 -> 6 -> NULL
    Second list is: -5 -> 7 -> NULL
    The final list would be: -5 -> 2 -> 6 -> 7 -> NULL

*/

/************************************************************

    Following is the linked list node structure

    template <typename T>
    class Node {
        public:
        T data;
        Node* next;

        Node(T data) {
            next = NULL;
            this->data = data;
        }

        ~Node() {
            if (next != NULL) {
                delete next;
            }
        }
    };

************************************************************/
#include<queue>
Node<int>* mergeKLists(vector<Node<int>*> &listArray)
{
    priority_queue<int, vector<int>, greater<int> > minheap;
    
    int size = listArray.size();    
    for(int i=0; i<size; i++)
    {
        Node<int>* temp = listArray[i];
        while(temp != NULL)
        {
            minheap.push(temp-> data);
            temp = temp-> next;
        }
    }
    
    Node<int>* head = new Node<int> (0);
    Node<int>* tail = head;
    
    while(!minheap.empty())
    {
        tail -> next = new Node<int> (minheap.top());
        minheap.pop();
        tail = tail -> next;
    }
    
    return head -> next;
}
// Approach -1 (runs fine for cases, but give TLE while submitting)
// Time : O(N*k*log(N*k) )
// Space : O(N*k)



/************************************************************************************************/
// Approach - 2
// Time : O(N*k*log(k) )    // as it's 'k' sized heap
// Space : O(k)
/*
    Create a minheap to store the head of all LL.
    and see the below process on how to enter element in LL
*/


#include<queue>
class compare
{
    public:
    bool operator() (Node<int>* a, Node<int>* b)
    {return (a->data > b->data);}
};
Node<int>* mergeKLists(vector<Node<int>*> &listArray)
{
    priority_queue<Node<int>*, vector<Node<int>*>, compare > minheap;
    
    int k = listArray.size();  
    if(k==0)
        return NULL;
    
    // Step 1 : pushing element (time = O(KlogK))
    for(int i=0; i<k; i++)
        if(listArray[i] != NULL)
            minheap.push(listArray[i]);
    
    Node<int>* head = NULL;
    Node<int>* tail = NULL;
    
    while(!minheap.empty())
    {
        Node<int>* top = minheap.top();
        minheap.pop();
        
        if(top -> next != NULL)
                minheap.push(top->next);
        
        if(head == NULL) // Empty LL   
        {
            head = top;
            tail = top;
   
        }
        else
        {    // Insert at end of LL
            tail -> next = top;
            tail = top;
        }
    }
    return head;
}