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

void insertNode(node* &tail, int element, int d)
{   
    //empty list
    if(tail == NULL)
    {
        node* newnode = new node(d);
        tail = newnode;
        newnode -> next = newnode;
    }
    else
    {
        //non-emopty list
        //assuming that the element is present in the list
        node* curr = tail;

        while(curr -> data != element)
        {
            curr = curr -> next;
        }

        // elemement found : curr is representing that node
        node* temp = new node(d);
        temp -> next = curr -> next; 
        curr -> next = temp;

    }
}

void print(node* tail)
{
    //Empty list
    if(tail == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    node* temp = tail;

    do {
        cout<<tail -> data<<" ";
        tail = tail -> next;
    } while(tail != temp);
    cout<<endl;

   /* 
    cout<<tail -> data<< " ";   // Bcz while loop will not print if only one node is there
    while(tail -> next != temp)
    {
        cout<<tail -> data<<" ";
        tail = tail -> next;
    }
    cout<< " ";
    */
}

void deletenode(node* &tail, int value)
{
    //empty list
    if(tail == NULL)
    {
        cout<<"List is empty "<<endl;
        return;
    }
    else{
        //non-empty
        //assuming the "value" is present in the linked list
        node* prev = tail;
        node* curr = prev -> next;
        
        while(curr -> data != value)
        {
            prev = curr;
            curr = curr -> next;
        }

        prev -> next = curr-> next;
        //1 node linked list
        if(curr == prev)
        {
            tail = NULL;
        }
        // >2 node linked list
        if(tail == curr)
        {
            tail = prev;
        }
        curr-> next = NULL;
        delete curr;
    }
}

int main()
{
    // Creating new node
    //node* node1 = new node(10);

    node* tail = NULL;

    //Inserting in empty list
    insertNode(tail, 5, 3);
    print(tail);
    insertNode(tail, 3, 7);
    print(tail);
    insertNode(tail, 7, 45);
    print(tail);
    insertNode(tail, 45, 90);
    print(tail);
    insertNode(tail, 7, 99);
    print(tail);
    
    deletenode(tail, 3);
    print(tail);

    return 0;
}