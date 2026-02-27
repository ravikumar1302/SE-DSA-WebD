#include<iostream>
#include<map>
using namespace std;


class node
{
    public:
    int data;
    node* next;

    node(int data) // Constructor
    {
        this -> data = data;
        this -> next = NULL;
    }
    ~node()     // Destructor
    {
        int value = this -> data;
        // Memory Free
        if(this -> next != NULL)
        {
            delete next;
            this -> next = NULL;
        }
        cout<<"Memory is free for node with data "<<value<<endl;
    }
};

// Inserting new node at starting 
void insertAtHead (node* &head, int d)  // Here refrence is taken so that NO new copy is made, and changes are made in original linked list
{
    node* temp = new node(d);  //new node
    temp -> next = head;
    head = temp;
}

// Inserting new node at last
void insertAtTail (node* &tail, int d)
{
    node* temp = new node(d);  //new node
    tail -> next =temp;
    // tail = tail -> next;
    tail = temp;    // it is same as above line
}

// Inserting new node at any position
void insertAtPosition (node* &tail, node* &head, int position, int d)
{
    // Inserting at start
    if(position == 1)
    {
        //this function will not be able to insert in start and end, as it need address of preevious node
        insertAtHead(head, d);
        return;
    }   

    node* temp = head;
    int cnt = 1;
    while(cnt < position -1 )
    {
        temp = temp -> next;
        cnt++;
    }

    // Inserting at last
    if(temp -> next == NULL)
    {
        insertAtTail(tail, d);
        return ;
    }
        
    //Creating new node for d
    node* nodeToInsert = new node(d);
    nodeToInsert -> next = temp -> next;
    temp -> next = nodeToInsert;
}

void print(node* &head)
{
    node* temp = head;
    
    while(temp != NULL)
    {
        cout<<temp -> data<<" ";
        temp = temp -> next;
    }
    cout<<endl;
}


bool detectLoop(node* head)
{
    if(head == NULL)
    {
        return false;
    }
    map<node*, bool> visited;
    node* temp = head;
    while(temp != NULL)
    {
        //Cycle is present
        if(visited[temp] == true )
        {
            cout<<"Present on element "<<temp -> data<<endl;
            return 1;
        }
        visited[temp] = true;
        temp = temp -> next;

    }
    return false;
}
//T.C. = O(N)
//S.C. = O(N)

//Floyd's Cycle Detection Algorithm (S.C. : O(1))
node* floydDetectLoop(node* head)
{
    if(head == NULL)
        return NULL;
    
    node* slow = head;
    node* fast = head;

    while(slow != NULL && fast != NULL)
    {
        fast = fast -> next;
        if(fast != NULL)
            fast = fast -> next;
       /* if(fast == NULL) //For case where 1 element is there and it's not loop
            return false; */
        slow = slow -> next;

        if(slow == fast)
        {
            cout<<"present at "<<slow -> data<<endl;
            return slow;
        }
    }
    return NULL;
}

node* getStartingNode(node* head)
{
    if(head == NULL)
        return NULL;
    node* intersection = floydDetectLoop(head);
    if(intersection == NULL)
        return NULL;
    node* slow = head;

    while(slow !=  intersection)
    {
        slow = slow -> next;
        intersection = intersection -> next; 
    }
    return slow;
}

void removeLoop(node* head)
{
    if(head == NULL)
        return;
    
    node* startOfLoop = getStartingNode(head);
    if(startOfLoop == NULL)
        return head;
    node* temp = startOfLoop;

    while(temp -> next != startOfLoop)
        temp = temp -> next;
    temp -> next = NULL;
}

int main()
{
    // Creating new node
    node* node1 = new node(10);
    //cout<<node1 -> data<<endl;
    //cout<<node1 -> next<<endl;

    //  Printing the linked list
    node* head = node1;
    node* tail = node1; 
    insertAtHead(head, 12);
    insertAtHead(head, 15);
    insertAtTail(tail, 19);  
    insertAtTail(tail, 22); 
    insertAtPosition(tail, head, 3, 45);    
    insertAtPosition(tail, head, 1, 75);
    insertAtPosition(tail, head, 8, 95);

    print(head);

    tail ->next = head -> next;

    if(detectLoop(head))
        cout<<"Cycle is present "<<endl;
    else
        cout<<"Not present "<<endl;

    node* loop = getStartingNode(head);
    cout<<"Starting node of cycle at "<<loop -> data<<endl;

    removeLoop(head);
    print(head);
    cout<<endl;
    cout<<"head "<<head -> data<<endl;
    cout<<"tail "<<tail -> data<<endl;
    return 0;
}