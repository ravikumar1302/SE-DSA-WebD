// Insertion and Deletion in a Singly Linked List

#include<iostream>
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

void deleteNode(int position, node* &head, node* & tail)
{
    // Deleting first node
    if(position == 1)
    {
        node* temp = head;
        head = head -> next;
        // Memory free for start node
        temp -> next = NULL;
        delete temp;
    }
    else
    {
        // Deleting any middle node or last node
        node* curr = head;
        node* prev = NULL;

        int cnt = 1;
        while(cnt < position)
        {
            prev = curr;
            curr = curr -> next;
            cnt++;
        }

         if(curr -> next == NULL)   // if last node
         {
            tail = prev;    // Without this, if the last node is deleted, than the tail node will point to garbage value rather than prev
        }
        prev -> next = curr -> next;
        curr -> next = NULL;
        delete curr;
    }
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
    cout<<endl<<"Inserting at head "<<endl;
    print(head);    
    insertAtHead(head, 12);
    print(head);    
    insertAtHead(head, 15);
    print(head);    

    cout<<endl<<"Inserting at tail "<<endl;
    print(head);    
    insertAtTail(tail, 19);
    print(head);    
    insertAtTail(tail, 22);
    print(head);  

    cout<<endl<<"Inserting 45 at position 3 "<<endl;
    print(head);    
    insertAtPosition(tail, head, 3, 45);
    print(head);

    cout<<endl<<"Inserting 75 at position 1 "<<endl;
    print(head);    
    insertAtPosition(tail, head, 1, 75);
    print(head);

    cout<<endl<<"Inserting 95 at position 8 "<<endl;
    print(head);    
    insertAtPosition(tail, head, 8, 95);
    print(head);

    cout<<"Deleting node"<<endl;
    deleteNode(8, head, tail);
    print(head);

    cout<<endl;
    cout<<"head "<<head -> data<<endl;
    cout<<"tail "<<tail -> data<<endl;
    
    //delete node1;
    return 0;
}