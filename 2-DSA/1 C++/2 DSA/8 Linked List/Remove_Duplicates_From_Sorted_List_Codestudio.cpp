/*
Remove_Duplicates_From_Sorted_List_Codestudio
Remove Duplicates from Sorted List Leetcode_83

You want to play with your friend, but your friend has pending homework, help him complete that.
You are given a ‘Head’ of a sorted linked list. You can remove some values from the linked list. In the end, you must return a sorted linked list that contains no adjacent values that are equal.
    For Example :
    If the given linked list is: 1 -> 2 -> 2 -> 3

    Then we will delete the duplicate value ‘2’ present in the linked list, and finally return the following list:
    1 -> 2 -> 3
*/

/************************************************************

    Following is the linked list node structure.
    
    class Node 
    {
        public:
        int data;
        Node* next;

        Node(int data) 
        {
            this->data = data;
            this->next = NULL;
        }
    };
    
************************************************************/

Node * uniqueSortedList(Node * head) {
    //empty list
    if(head == NULL)
        return NULL;

    //non-empty list
    Node* curr = head;

    while(curr != NULL)
    {
        if( (curr -> next != NULL) && curr -> data == curr -> next -> data)
        {
            Node* next_next = curr -> next -> next;
            Node* nodeToDelete = curr -> next;
            delete(nodeToDelete);
            curr -> next = next_next;
        }
        else    //not equal
        {
            curr = curr -> next;
        }
    }
    return head;
}