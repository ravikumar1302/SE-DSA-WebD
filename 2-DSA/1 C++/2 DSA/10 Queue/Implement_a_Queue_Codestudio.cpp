/*
Implement_a_Queue_Codestudio

mplement a Queue Data Structure specifically to store integer data using a Singly Linked List or an array.
You need to implement the following public functions :
1. Constructor: It initializes the data members as required.

2. enqueue(data): This function should take one argument of type integer. It enqueues the element into the queue.

3. dequeue(): It dequeues/removes the element from the front of the queue and in turn, returns the element being dequeued or removed. In case the queue is empty, it returns -1.

4. front(): It returns the element being kept at the front of the queue. In case the queue is empty, it returns -1.

5. isEmpty(): It returns a boolean value indicating whether the queue is empty or not.
*/

class Queue {
public:
    int qfront;
    int rear;
    int *arr;
    int size;
    
    Queue() {
        size = 10000;
        arr = new int[size];
        qfront = 0;
        rear = 0;
    }

    /*----------------- Public Functions of Queue -----------------*/

    bool isEmpty() {
        if(rear == qfront)  //Rear in queue represent the next empty area, we firstly enter the data, and then modify the rear
            return true;
        else
            return false;
    }

    void enqueue(int data) {
        if(rear == size)
            return;    //Queue is full
        else
        {
            arr[rear] = data;
            rear++;
        }
    }

    int dequeue() {
        if(qfront == rear)
            return -1;    //Queue is empty
        else
        {
            int ans = arr[qfront];
            arr[qfront] = -1;
            qfront++;
            if(qfront == rear)
            {
                qfront = rear = 0; // to start from 0, after queue is empty
            }
            return ans;
        }
    }

    int front() {
        if(qfront != rear)
            return arr[qfront];
        else
            return -1;
    }
};

// T.C> : O(N) of all above functions