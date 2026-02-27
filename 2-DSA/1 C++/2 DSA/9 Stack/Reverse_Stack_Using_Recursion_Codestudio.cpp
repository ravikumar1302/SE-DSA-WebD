/*
Reverse_Stack_Using_Recursion_Codestudio

Reverse a given stack of integers using recursion.
*/

void insertAtBottom(stack<int> &s, int element)
{
    //base case 
    if(s.empty())
    {
        s.push(element);
        return;
    }
        
    //calculation
    int num = s.top();
    s.pop();
    
    //recursion
    insertAtBottom(s, element);
    
    s.push(num);
}

void reverseStack(stack<int> &stack) {
    //base case
    if(stack.empty())
        return;
    int top = stack.top();
    stack.pop();
    
    //Recursion
    reverseStack(stack);
    
    insertAtBottom(stack, top);
}

// T.C. : O(N^2)