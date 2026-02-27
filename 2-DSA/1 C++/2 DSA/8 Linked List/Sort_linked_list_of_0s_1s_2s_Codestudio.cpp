/*
Sort_linked_list_of_0s_1s_2s_Codestudio

You are given a linked list having N number of nodes and each node will have an integer which can be 0, 1, or 2. You have to sort the given linked list in ascending order.
    For Example:
    Let the linked list be 1→0→2→1→2. 
    The sorted linked list for the given linked list will be 0→1→1→2→2.
*/

/********************************
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

********************************/

//Approach-1 
//Coutning the no of zeros, ones and twos and then replacing elements in main linked list
Node* sortList(Node *head)
{
    int zero = 0;
    int one = 1;
    int two = 2;
    Node* temp = head;
    while(temp != NULL)
    {
        if(temp -> data == 0)
            zero++;
        else if(temp -> data == 1)
            one++;
        else
            two++;
        temp = temp ->next;
    }
    temp = head;
    while(temp != NULL)
    {
        if(zero != 0)
        {
            temp -> data= 0;
            zero--;
        }
        else if(one != 1)
        {
            temp -> data= 1;
            one--;
        }
        else
        {
            temp -> data = 2;
            two--;
        }
        temp = temp -> next;
    }
    return head;

}


//Approach-2 (Data replacement not allowed) 
// As data replacement not allowed, links need to be change then

void insertAtTail(Node* &tail, Node* curr ) {
    tail -> next = curr;
    tail = curr;
}


Node* sortList(Node *head)
{
    //Step-1: Declare pointers
    Node* zeroHead = new Node(-1);
    Node* zeroTail = zeroHead;
    Node* oneHead = new Node(-1);
    Node* oneTail = oneHead;
    Node* twoHead = new Node(-1);
    Node* twoTail = twoHead;
    
    Node* curr = head;
    
    //Step-2:  create separate list 0s, 1s and 2s
    while(curr != NULL) {
        
        int value = curr -> data;
        
        if(value == 0) {
            insertAtTail(zeroTail, curr);
        }
        else if(value == 1) {
            insertAtTail(oneTail, curr);
        }
        else if(value == 2) {
            insertAtTail(twoTail, curr);
        }       
        curr = curr -> next;
    }
    
    //Step-3: Merge 3 sublists
    
    // if 1s list not empty
    if(oneHead -> next != NULL) {
        zeroTail -> next = oneHead -> next;
    }
    else {
        //If 1s list is empty
        zeroTail -> next = twoHead -> next;
    }
    
    oneTail -> next = twoHead -> next;
    twoTail -> next = NULL;
    
	//Step-4: Setup head 
    head = zeroHead -> next;
    
    //Step-5: delete dummy nodes
    delete zeroHead;
    delete oneHead;
    delete twoHead;
    
    // Step-6: return ans
    return head;
}