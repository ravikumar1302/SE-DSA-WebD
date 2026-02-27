/*
Sort_a_Stack_Codestudio

You’re given a stack consisting of 'N' integers. Your task is to sort this stack in descending order using recursion.
We can only use the following functions on this stack S.
is_empty(S) : Tests whether stack is empty or not.
push(S) : Adds a new element to the stack.
pop(S) : Removes top element from the stack.
top(S) : Returns value of the top element. Note that this function does not remove elements from the stack.
*/

void sortedInsert(stack<int> &s, int num)
{
    // Base case
    if( s.empty() || (!s.empty() && s.top() < num) )
    {
        s.push(num);
        return;
    }
    int element = s.top();
    s.pop();
    
    //Recursion
    sortedInsert(s, num);
    
    s.push(element);
}

void sortStack(stack<int> &stack)
{
    //Base case
	if(stack.empty())    
        return ;
    
    int num = stack.top();
    stack.pop();
   
    //Recursion
    sortStack(stack);  
    
    sortedInsert(stack, num);
}

// T.C. : O(N^2)