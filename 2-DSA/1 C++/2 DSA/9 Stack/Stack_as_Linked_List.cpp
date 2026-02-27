//Implement Stack using Linked List
// A stack is a linear data structure where both insertion and deletion of elements take place at the top. 
//It follows FILO (First In Last Out) or LIFO (Last In First Out) approaches. 
//Books piled on top of each other is an example of a stack, where you can only remove a single book at a time, which is at the top of the stack. 
//Likewise, you can only add a single book at a time, on the top of the stack only.


#include<iostream>
using namespace std;

class Node
{   
    public:
    int data;
    Node* next;

    //constructor
    Node(int data)
    {
        this -> data= data;
        this -> next= NULL;

    }

    //Destructor
    ~Node()
    {
        int value=this->data;
        while(this->next!=NULL)
        {
            this->next=NULL;
            delete next;
        }    
        cout<<" Memory deleted with the value as "<<value<<endl;
    }
};

class Stack
{
    public:

    int size;
    Node* head;

    Stack()
    {
        head=NULL;
        size=0;

    }

    void push(int data) //Basically, stack insertion and deletion occurs only at head of linked list
    {
        Node* temp= new Node(data);
        //temp->data= data;
        temp->next= head;
        head=temp;
    }

    void pop()
    {
        if(head==NULL)
            cout<<" Stack is empty "<<endl;
        else
            {
                Node* temp=head;
                head=head->next;
                delete temp;
            }
    }

    int peak()
    {
        if(head!=NULL)
        {
            int value= head->data;
            return value;
        }
        else
            return -1;
        
    }
};

int main()
{
    Stack st;
    st.push(5);
    cout<< " Stack top is "<<st.peak()<<endl;
    st.push(6);
    st.pop();
    st.pop();
    st.pop();
    cout<< " Stack top is "<<st.peak()<<endl;
    st.push(7);
    cout<< " Stack top is "<<st.peak()<<endl;
    st.push(8);
    cout<< " Stack top is "<<st.peak()<<endl;
    st.push(9);
    cout<< " Stack top is "<<st.peak()<<endl;
    st.push(10);
    cout<< " Stack top is "<<st.peak()<<endl;

    return 0;
}



/*
// Using strut only

#include <iostream>
using namespace std;

struct Node {
   int data;
   struct Node *next;
};

struct Node* top = NULL;
void push(int val) {
   struct Node* newnode = (struct Node*) malloc(sizeof(struct Node));
   newnode->data = val;
   newnode->next = top;
   top = newnode;
}

void pop() {
   if(top==NULL)
   cout<<"Stack Underflow"<<endl;
   else {
      cout<<"The popped element is "<< top->data <<endl;
      top = top->next;
   }
}

void display() {
   struct Node* ptr;
   if(top==NULL)
   cout<<"stack is empty";
   else {
      ptr = top;
      cout<<"Stack elements are: ";
      while (ptr != NULL) {
         cout<< ptr->data <<" ";
         ptr = ptr->next;
      }
   }
   cout<<endl;
}

int main() {
   int ch, val;
   cout<<"1) Push in stack"<<endl;
   cout<<"2) Pop from stack"<<endl;
   cout<<"3) Display stack"<<endl;
   cout<<"4) Exit"<<endl;
   do {
      cout<<"Enter choice: "<<endl;
      cin>>ch;
      switch(ch) {
         case 1: {
            cout<<"Enter value to be pushed:"<<endl;
            cin>>val;
            push(val);
            break;
         }
         case 2: {
            pop();
            break;
         }
         case 3: {
            display();
            break;
         }
         case 4: {
            cout<<"Exit"<<endl;
            break;
         }
         default: {
            cout<<"Invalid Choice"<<endl;
         }
      }
   }while(ch!=4);
   return 0;
}

*/


/*
//Using struct and class
struct node
{ int info;
  struct node *next;
};

class stack
{ struct node *top;
  public:
  stack();
  void push();
  void pop();
  void display();
  //void exit();
};

stack::stack()
{ top=NULL;
}

void stack::push()
{ int data;
  struct node *p;
  if(((node *)malloc(sizeof(node)))==NULL)
  { cout<<" MEMORY EXHAUSTED ";
  }
  cout<<"enter a number to be inserted :";
  cin>>data;
  p=new node;
  p->info=data;
  p->next=NULL;
  if(top!=NULL)
  { p->next=top;
  }
  top=p;
  cout<<"\n new item inserted"<<endl;
}

void stack::pop()
{ struct node * temp;
  if(top==NULL)
  { cout<<"the stack is empty"<<endl;
  }
  else
  { temp=top;
    top=top->next;
    cout<<"the value popped is"<<temp->info<<endl;
    delete temp;
  }
}

void stack::display()
{ struct node *p=top;
  if(top==NULL)
  { cout<<"nothing to display\n";
  }
  else
  { cout<<"the contents of stack\n";
    while(p!=NULL)
    { cout<<p->info<<endl;
      p=p->next;
    }
  }
}

int main()
{ clrscr();
  stack s;
  int choice;
  do
  { cout<<"\n enter your choice:";
    cout<<"\n 1.PUSH\n 2.POP\n 3.DISPLAY\n 4.EXIT\n";
    cin>>choice;
    switch(choice)
    { case 1: s.push();  break;
      case 2: s.pop();   break;
      case 3: s.display();   break;
     // case 4: exit(0);    break;
      default: cout<<"invalid choice";  break;
    }
   }while(choice);
   getch();
   return 0;
}

*/