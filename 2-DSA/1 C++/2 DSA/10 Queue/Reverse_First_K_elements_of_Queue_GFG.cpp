/*
Reverse_First_K_elements_of_Queue_GFG

Given an integer K and a queue of integers, we need to reverse the order of the first K elements of the queue, leaving the other elements in the same relative order.

Only following standard operations are allowed on queue.

enqueue(x) : Add an item x to rear of queue
dequeue() : Remove an item from front of queue
size() : Returns number of elements in queue.
front() : Finds front item.
Note: The above operations represent the general processings. In-built functions of the respective languages can be used to solve the problem.
    Example 1:

    Input:
    5 3
    1 2 3 4 5

    Output: 
    3 2 1 4 5

    Explanation: 
    After reversing the given
    input from the 3rd position the resultant
    output will be 3 2 1 4 5.
Expected Time Complexity : O(n)
Expected Auxiliary Space : O(n)
*/

queue<int> modifyQueue(queue<int> q, int k) {
    deque<int> q1;
    
    //APPROACH
    //entering first k elements in deque from front
    //then entering remaning elments from back
    //Now copy deque in queue
    
    while(k)    //entering first k elements in deque from front
    {
        int num = q.front();
        q.pop();
        q1.push_front(num);
        k--;
    }
   
    
    int n = q.size();
    while(n)    //then entering remaning elments from back
    {
        int num = q.front();
        q.pop();
        q1.push_back(num);
        n--;
    }
    
    n = q1.size();
    while(n)    //Now copy deque in queue
    {
        int num = q1.front();
        q1.pop_front();
        q.push(num);
        n--;
    }
    return q;
}



queue<int> modifyQueue(queue<int> q, int k) {
    
    //algo:Using Stack
    //first k element stack me daaldo  and queue se hatado
    // k element stack se nikalke wapas queue me daalde 
    // fer queue k (n-k) starting k elements, wapas queue me daalde
    
    stack<int> s;
    
    for(int i = 0; i<k; i++) {
        int val = q.front();
        q.pop();
        s.push(val);
    }
    
    while(!s.empty()) {
        int val = s.top();
        s.pop();
        q.push(val);
    }
    
    int t = q.size()-k;
    
    while(t--) {
        int val = q.front();
        q.pop();
        q.push(val);
    }
    
    return q;
}