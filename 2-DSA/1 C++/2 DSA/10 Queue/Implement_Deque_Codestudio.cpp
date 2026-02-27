/*
Implement_Deque_Codestudio

Design a data structure to implement deque of size ‘N’. It should support the following operations:
    pushFront(X): Inserts an element X in the front of the deque. Returns true if the element is inserted, otherwise false.

    pushRear(X): Inserts an element X in the back of the deque. Returns true if the element is inserted, otherwise false.

    popFront(): Pops an element from the front of the deque. Returns -1 if the deque is empty, otherwise returns the popped element.

    popRear(): Pops an element from the back of the deque. Returns -1 if the deque is empty, otherwise returns the popped element.

    getFront(): Returns the first element of the deque. If the deque is empty, it returns -1.

    getRear(): Returns the last element of the deque. If the deque is empty, it returns -1.

    isEmpty(): Returns true if the deque is empty, otherwise false.

    isFull(): Returns true if the deque is full, otherwise false.
*/

class Deque
{
public:
    // Initialize your data structure.
    int *arr;
    int front;
    int rear;
    int size;
    
    Deque(int n)
    {
        size = n;
        arr = new int[n];
        front = rear = -1;
    }

    // Pushes 'X' in the front of the deque. Returns true if it gets pushed into the deque, and false otherwise.
    bool pushFront(int x)
    {
        if( isFull() )    //is full
            return false;
        else if(isEmpty())    //entering first element
            front = rear =0;
        else if(front == 0 && rear != size-1)    //front at 0 and rear not at last
            front = size-1;
        else    //Normal case
            front--;
        
        arr[front] = x;
        return true;
    }

    // Pushes 'X' in the back of the deque. Returns true if it gets pushed into the deque, and false otherwise.
    bool pushRear(int x)
    {
        if( isFull() )    //Is full
            return false;
        else if(isEmpty())    //entering first element
            front = rear = 0;
        else if(rear == size-1 && front != 0)     //Rear in end and front not at start
            rear = 0;    //To maintain cyclic nature
        else
            rear++;
        
        arr[rear] = x;
        return true;
    }

    // Pops an element from the front of the deque. Returns -1 if the deque is empty, otherwise returns the popped element.
    int popFront()
    {
        if(isEmpty())    //is empty
            return -1;
            
        int ans = arr[front];
        arr[front] = -1;
        
        if(front == rear)    //Single element is there
            front = rear = -1;
        else if(front == size-1 )
            front = 0;    //To maintain cyclic nature
        else    //Normal flow
            front++;
        
        return ans;
    }

    // Pops an element from the back of the deque. Returns -1 if the deque is empty, otherwise returns the popped element.
    int popRear()
    {
        if(isEmpty())    //Empty
            return -1;
        
        int ans = arr[rear];
        arr[rear] = -1;
        
        if(front == rear)    //single element is present
            front = rear = -1;
        else if(rear == 0)
            rear = size-1;    //To maintain cyclic nature
        else    //Normal Flow
            rear--;
        
        return ans;
    }

    // Returns the first element of the deque. If the deque is empty, it returns -1.
    int getFront()
    {
        if(isEmpty())    //Empty
            return -1;
        else
            return arr[front];
    }

    // Returns the last element of the deque. If the deque is empty, it returns -1.
    int getRear()
    {
        if(isEmpty())    //Empty
            return -1;
        else
            return arr[rear];
    }

    // Returns true if the deque is empty. Otherwise returns false.
    bool isEmpty()
    {
        if(front == -1)
            return true;
        else
            return false;
    }

    // Returns true if the deque is full. Otherwise returns false.
    bool isFull()
    {
        if( (front == 0 && rear == size-1) || (front != 0 && rear == (front-1)%(size-1) ) )
            return true;
        else 
            return false;
    }
};