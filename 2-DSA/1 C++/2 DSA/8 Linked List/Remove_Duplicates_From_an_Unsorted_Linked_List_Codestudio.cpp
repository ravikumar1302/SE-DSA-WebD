/*
Remove_Duplicates_From_an_Unsorted_Linked_List_Codestudio
Remove duplicates from an unsorted linked list_GFG

You are given a linked list of N nodes. Your task is to remove the duplicate nodes from the linked list such that every element in the linked list occurs only once i.e. in case an element occurs more than once, only keep its first occurrence in the list.
    For Example :
    Assuming the linked list is 3 -> 2 -> 3 -> 4 -> 2 -> 3 -> NULL.

    Number ‘2’ and ‘3’ occurs more than once. Hence we remove the duplicates and keep only their first occurrence. So, our list becomes : 3 -> 2 -> 4 -> NULL.
*/

/****************************************************************
    Following is the class structure of the Node class:
    class Node
    {
    public:
        int data;
        Node *next;
        Node(int data)
        {
            this->data = data;
            this->next = NULL;
        }
    };
*****************************************************************/
#include<bits/stdc++.h>
Node *removeDuplicates(Node *head)
{
    Node* curr = head;
    Node* prev = NULL;
    unordered_map<int, int> visited;
    
    while(curr != NULL)
    {
        //Not visited
        if( !visited[curr->data] )    
        {
            visited[curr->data] = 1;
            prev = curr;
            curr = curr -> next;
        }
        //if visited, then delete
        else{
            prev -> next = curr -> next;
            delete curr;
            //curr = prev -> next;  //Either write it here or after else condition, meaning remain same
        }
        curr = prev -> next;
    }
    return head;
}