/*
Queue_Reversal_GFG

Given a Queue Q containing N elements. The task is to reverse the Queue. Your task is to complete the function rev(), that reverses the N elements of the queue.

    Example 1:

    Input:
    6
    4 3 1 10 2 6

    Output: 
    6 2 10 1 3 4

    Explanation: 
    After reversing the given
    elements of the queue , the resultant
    queue will be 6 2 10 1 3 4.

Expected Time Complexity : O(n)
Expected Auxilliary Space : O(n)
*/

queue<int> rev(queue<int> q)
{
    //Approach 1: Using Stack
    stack<int> s;
    while(!q.empty())
    {
        int element = q.front();
        q.pop();
        s.push(element);
    }
    while(!s.empty())
    {
        int element = s.top();
        s.pop();
        q.push(element);
    }
    return q;
}


//Using Recursion
void  fun(queue<int> &q){
    if(q.empty())
        return ;
    
    int num = q.front();
    q.pop();
    
    fun(q);
    q.push(num);
}
queue<int> rev(queue<int> q)
{
    // add code here.
   
    fun(q);
    
    return q;
}