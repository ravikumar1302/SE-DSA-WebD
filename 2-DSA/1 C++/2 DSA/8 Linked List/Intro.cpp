#include<iostream>
using namespace std;

class node
{
    public:
    int data;
    node* next;

    node(int data) //Constructor
    {
        this -> data = data;
        this -> next = NULL;
    }
};

int main()
{
    // Creating new node
    node* node1 = new node(10);
    cout<<node1 -> data<<endl;
    cout<<node1 -> next<<endl;

    // Deleting the dynamically created nodes
    delete node1;
    return 0;
}