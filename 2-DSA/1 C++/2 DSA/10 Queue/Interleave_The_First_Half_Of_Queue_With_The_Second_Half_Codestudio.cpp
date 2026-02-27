/*
Interleave_The_First_Half_Of_Queue_With_The_Second_Half_Codestudio

Problem Statement
You have been given a queue of integers. You need to rearrange the elements of the queue by interleaving the elements of the first half of the queue with the second half.
Note :
The given queue will always be of even length.
    For Example :
    If N= 10
    and Q = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    then the output will be
    Q = [10, 60, 20, 70, 30, 80, 40, 90, 50, 100]

OR
Given a queue of integers of even length, rearrange the elements by interleaving the first half of the queue with the second half of the queue. 
Only a stack can be used as an auxiliary space. Examples:

    Input :  1 2 3 4
    Output : 1 3 2 4

    Input : 11 12 13 14 15 16 17 18 19 20
    Output : 11 16 12 17 13 18 14 19 15 20

*/

// Approach-1 (Using another queue) : enter first half in another queue and then enter elements in original queue one from orignal and one from new till new is empty

//Approach-2: (Using Stack)

void interLeaveQueue(queue < int > & q) {
    stack<int>st;
    int qlen=q.size()/2;
    //Step-1: taking first half into stack
    for(int i=0;i<qlen;i++)
    {
        st.push(q.front());
        q.pop();
    }
    //Step-2 : inserting that first half in last of queue
    while(!st.empty())
    {
        q.push(st.top());
        st.pop();
    }
    //Step-3: inserting first half of queue to back of queue
    for(int i=0;i<qlen;i++){
        q.push(q.front());
        q.pop();
    }
    //Step-4: taking first half into stack, so that we can get the first half in original order in stack as in original queue
    for(int i=0;i<qlen;i++){
        st.push(q.front());
        q.pop();
    }
   //Step 5: Now enter one element from queue and one from stack
   while(!st.empty()){
       q.push(st.top());
       st.pop();
       q.push(q.front());
       q.pop();
   }
    return;
}