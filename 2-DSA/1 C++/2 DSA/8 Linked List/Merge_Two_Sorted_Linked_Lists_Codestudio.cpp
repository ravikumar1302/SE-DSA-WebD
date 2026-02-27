/*
Merge_Two_Sorted_Linked_Lists_Codestudio

You are given two sorted linked lists. You have to merge them to produce a combined sorted linked list. You need to return the head of the final linked list.
Note:
The given linked lists may or may not be null.
    
    For example:
    If the first list is: 1 -> 4 -> 5 -> NULL and the second list is: 2 -> 3 -> 5 -> NULL

    The final list would be: 1 -> 2 -> 3 -> 4 -> 5 -> 5 -> NULL
    */

   #include <bits/stdc++.h> 
/************************************************************

    Following is the linked list node structure.
    
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
Node<int>* solve(Node<int>* first, Node<int>* second)
{
    //If only one element is present in first list
    if(first -> next == NULL)
    {
        first -> next = second;
        return first;
    }

    Node<int>* curr1 = first;
    Node<int>* next1 = curr1 -> next;
    Node<int>* curr2 = second;
    Node<int>* next2 = curr2 -> next;

    while(next1 != NULL && curr2!= NULL)
    {
        if( (curr2 -> data >= curr1 -> data) && (curr2 -> data <= next1 -> data))
        {
            //add node in between the first list
            curr1 -> next = curr2;
            next2 = curr2 -> next;
            curr2 -> next = next1;
            
            // Update pointers
            curr1 =  curr2;
            curr2 = next2;
        }

        else
        {
            //go one step ahead in first list
            curr1 = next1;  //OR curr1 = curr1 -> next;
            next1 = next1 -> next;

            if(next1 == NULL)
            {
                curr1 -> next = curr2;
                return first;
            }
        }
    }
    return first;
}


Node<int>* sortTwoLists(Node<int>* first, Node<int>* second)
{
    if(first == NULL)
        return second;
    if(second == NULL)
        return first;

    if(first -> data <= second -> data)
        return solve(first, second);
    else
        return solve(second, first);
}
// Space: O(1), as same list is updated


// Approach-2
// Space : O(N), as ans list is used

void insertAtTail(Node<int>* &tail, Node<int>* temp)
{
    tail->next = temp;
    tail = temp;
}
Node<int>* sortTwoLists(Node<int>* first, Node<int>* second)
{
    
    Node<int>* ans = new Node<int>(-1);
    Node<int>* tail = ans;
    Node<int>* cur1 = first;
    Node<int>* cur2 = second;
    
    while( cur1 && cur2)
    {
        if(cur1->data < cur2->data)
        {
            insertAtTail(tail, cur1);
            cur1= cur1->next;
        }
        else
        {
            insertAtTail(tail, cur2);
            cur2 = cur2->next;
        }
    }
    while(cur1)
    {
            insertAtTail(tail, cur1);
            cur1= cur1->next;
    }
    while(cur2)
    {
            insertAtTail(tail, cur2);
            cur2 = cur2->next;
   }
    return ans->next;
}