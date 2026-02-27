/*
Circular_Queue_Codestudio

You will be given ‘Q’ queries. You need to implement a circular queue according to those queries. Each query will belong to one of these two types:
1 ‘X’: Enqueue element ‘X’ into the end of the nth queue. Returns true if the element is enqueued, otherwise false.

2: Dequeue the element at the front of the nth queue. Returns -1 if the queue is empty, otherwise, returns the dequeued element.
*/

class CircularQueue{
    public:
    // Initialize your data structure.
    int *arr;
    int front;
    int rear;
    int size;
    
    CircularQueue(int n){
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    // Enqueues 'X' into the queue. Returns true if it gets pushed into the stack, and false otherwise.

    //Rear in Circular queue represent the last element area, we modify rear and then enter data. (Different than normal queue)
    bool enqueue(int value){
        if( (front == 0 && rear == size-1) || (rear == (front-1)%(size-1) ) )
            return false;    //Queue is full
        else if(front == -1)    //First element to enter (empty queue)
            front = rear= 0;
        else if(rear == size-1 && front != 0)    //Rear in end and front not at start
            rear = 0;    //To maintain cyclic nature
        else        ////Normal flow, any other normal case
            rear++;
        
        arr[rear] = value;
        return true;
    }

    // Dequeues top element from queue. Returns -1 if the stack is empty, otherwise returns the popped element.
    int dequeue(){
        if(front == -1)    //Queue is empty
            return -1;
        
        int ans = arr[front];
        arr[front] = -1;
        
        if(front == rear)     //single element is present
            front = rear = -1;
        else if(front == size - 1)
            front = 0;    //To maintain cyclic nature
        else    //Normal flow
            front++;
        
        return ans;
    }
};