/*
Circularly_Linked_Codestudio

You are given the head of a linked list containing integers, You need to find out whether the given linked list is circular or not.
Note :
1. A linked list is said to be circular if it has no node having its next pointer equal to NULL and all the nodes form a circle i.e. the next pointer of last node points to the first node.
2. An empty linked will also be considered as circular.
3. All the integers in the linked list are unique.
4. In the input, the next pointer of a node with i’th integer is linked to the node with data (i+1)’th integer (If (i+1)’th node exists). If there is no such (i+1)’th integer then the next pointer of such node is set to NULL.
*/

/*************************************************
        Following is the structure of class Node:
     
        class Node{
        public:
            int data;
            Node* next;
            
            Node(int data){
                this->data = data;
                this->next = NULL;
            }
            
        }
**************************************************/

bool isCircular(Node* head){
    if(head == NULL)    // Empty list
        return true;
    Node* temp = head -> next;
    while(temp != NULL && temp != head)
        temp = temp -> next;
    if(temp == head)
        return true;
    return false;
}
