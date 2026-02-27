
#include<iostream>
using namespace std;

class node
{
    public:
    int data;
    node* prev;
    node* next;

    //Constructor
    node(int d)
    {
        this -> data = d;
        this -> prev = NULL;
        this -> next = NULL;
    }
    ~node()
    {
        int value = this ->data;
        if(next != NULL)
        {
            delete next;
            next = NULL;
        }
        cout<< "Memory free for value : "<<value<<endl;
    }
};

void print(node* head)
{
    node* temp = head;
    while(temp != NULL)
    {
        cout<<temp -> data<<" ";
        temp = temp -> next;
    } 
    cout<<endl;
}

int length(node* head)  // Calculating length of Linked List
{
    int len = 0;
    node* temp = head;
    while(temp != NULL)
    {
        len++;
        temp = temp -> next;
    } 
    return len;
}

void insertAtHead(node* & tail, node* &head, int d)
{
    // Empty list
    if(head == NULL)
    {
        node* temp = new node(d);
        head = temp;
        tail = temp;
    }
    else
    {
        node* temp = new node(d);
        temp -> next = head;
        head -> prev = temp;
        head = temp;
    }
    
}

void insertAtTail(node* &tail, node* &head, int d)
{
    //Empty list
    if(tail == NULL)
    {
        node* temp = new node(d);
        tail = temp;
        head = temp;
    }
    else
    {
        node* temp = new node(d);
        tail -> next = temp;
        temp -> prev = tail;
        tail = temp;
    }
}

// Inserting new node at any position
void insertAtPosition (node* &tail, node* &head, int position, int d)
{
    //this function will not be able to insert in start and end, as it need address of previous node, so use above made function for that

    // Inserting at start
    if(position == 1)
    {        
        insertAtHead(tail, head, d);
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
        insertAtTail(tail, head, d);
        return ;
    }
        
    //Creating new node for d
    node* nodeToInsert = new node(d);
    nodeToInsert -> next = temp -> next;
    temp -> next -> prev = nodeToInsert;
    temp -> next = nodeToInsert;
    nodeToInsert -> prev = temp;
}

void deleteNode(int position, node* &head, node* & tail)
{
    // Deleting first node
    if(position == 1)
    {
        node* temp = head;
        temp -> next -> prev = NULL;
        head = temp -> next;
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

         if(curr -> next == NULL)
         {
            tail = prev;    // Without this, if the last node is deleted, than the tail node will point to garbage value rather than prev
        }
        curr -> prev = NULL;
        prev -> next = curr -> next;
        //curr -> next -> prev = prev;  //This line was not in lecture, but this should come acc to me
        curr -> next = NULL;
        delete curr;
    }
}

int main()
{
    /*
    node* node1 = new node(10);
    node* head = node1;
    node* tail = node1;
    print(head);
    */
    //Inserting at head in empty list
    node* head = NULL;
    node* tail = NULL;


    insertAtHead(tail, head, 22);
    print(head);
    insertAtHead(tail, head, 30);
    print(head);
    //cout<<"Length of linked list is : "<<length(head)<<endl;

    insertAtTail(tail, head, 45);
    print(head);
    insertAtTail(tail, head, 75);
    print(head);
    insertAtPosition(tail, head, 2, 100);
    print(head);

    deleteNode(3, head, tail);
    print(head);
    cout<<"Head "<<head -> data<<endl;
    cout<<"Tail "<<tail -> data<<endl;

    
    //delete node1;
    return 0;
}