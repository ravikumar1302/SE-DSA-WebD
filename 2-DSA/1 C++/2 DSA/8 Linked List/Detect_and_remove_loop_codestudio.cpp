/*
Detect_and_remove_loop_codestudio

Given a singly linked list, you have to detect the loop and remove the loop from the linked list, if present. You have to make changes in the given linked list itself and return the updated linked list.
Expected Complexity: Try doing it in O(n) time complexity and O(1) space complexity. Here, n is the number of nodes in the linked list.
Input format:
The first line of input contains two values: the number of nodes in the linked list and the value of the kth node from which the last node connects to form the loop while the second line of input contains the given linked list.
The value of k should be greater than or equal to 0 and less than equal to n. For, k equal to 0, there is no loop present in the linked list and for k equal to n, the last node is connected to itself to form the cycle.
*/

/*************************************************
    
    class Node {
        public :

        int data;
        Node *next;

        Node(int data) {
            this -> data = data;
            this -> next = NULL;
        }
    };

*************************************************/
//Floyd's Cycle Detection Algorithm
Node* floydDetectLoop(Node* head)
{
    if(head == NULL)
        return NULL;
    
    Node* slow = head;
    Node* fast = head;

    while(fast != NULL && fast -> next != NULL)
    {
        fast = fast -> next -> next;
        slow = slow -> next;
        
        if(slow == fast)
            return slow;
    }
    return NULL;
}

Node* getStartingNode(Node* head)
{
    if(head == NULL)
        return NULL;
    Node* intersection = floydDetectLoop(head);
    if(intersection == NULL)
        return NULL;
    Node* slow = head;

    while(slow !=  intersection)
    {
        slow = slow -> next;
        intersection = intersection -> next; 
    }
    return slow;
}

Node *removeLoop(Node *head)
{
     if(head == NULL)
        return NULL;

    // Step-1 : Find loop starting node
    Node* startOfLoop = getStartingNode(head);
    if(startOfLoop == NULL)         // No loop exists
        return head;
    Node* temp = startOfLoop;

    while(temp -> next != startOfLoop)
        temp = temp -> next;

    // Step-2 : Breaking the loop
    temp -> next = NULL;
    
    return head;
}