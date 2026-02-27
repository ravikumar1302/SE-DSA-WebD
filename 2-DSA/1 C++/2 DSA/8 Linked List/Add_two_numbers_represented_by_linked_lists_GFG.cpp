/*
Add_two_numbers_represented_by_linked_lists_GFG
Add Two Numbers Leetcode_2

Given two numbers represented by two linked lists of size N and M. The task is to return a sum list.
The sum list is a linked list representation of the addition of two input numbers from the last.

    Example 1:

    Input : N = 2, valueN[] = {4,5} and M = 3, valueM[] = {3,4,5}
    Output: 3 9 0  
    Explanation: For the given two linked list (4 5) and (3 4 5), after adding the two linked list resultant linked list will be (3 9 0).
*/

/*
struct Node {
    int data;
    struct Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

*/


class Solution
{
    private:
    Node* reverse(Node* head)
  {
      Node* curr = head;
      Node* prev = NULL;
      Node* next = NULL;
      
      while(curr != NULL)
      {
          next = curr -> next;
          curr -> next = prev;
          prev = curr;
          curr = next;
      }
      return prev;
  }
  
  void insertAtTail (struct Node* &head, struct Node* &tail, int val)
  {
    Node* temp = new Node(val);
    //empty list
    if(head == NULL)
    {
        head = temp;
        tail = temp;
        return;
    }
    else
    {
        tail -> next = temp;
        tail = temp;
    }
  }
  
  struct Node* add(struct Node* first, struct Node* second)
  {
      int carry = 0;
      Node* anshead = NULL;
      Node* anstail = NULL;
      while(first != NULL && second != NULL)
      {
          int sum = carry + first -> data + second -> data;
          int digit = sum%10;
          
          //create node and add in answer list
          insertAtTail(anshead, anstail, digit);
          
          carry = sum/10;
          first = first -> next;
          second = second -> next;
      }
      
      while(first != NULL)
      {
          int sum = carry + first -> data;
          int digit = sum%10;
          
          //create node and add in answer list
          insertAtTail(anshead, anstail, digit);
          
          carry = sum/10;
          first = first -> next;
      }
      while(second != NULL)
      {
          int sum = carry + second -> data;
          int digit = sum%10;
          
          //create node and add in answer list
          insertAtTail(anshead, anstail, digit);
          
          carry = sum/10;
          second = second -> next;
      }
      while(carry != 0)
      {
          int sum = carry;
          int digit = sum%10;
          
          //create node and add in answer list
          insertAtTail(anshead, anstail, digit);
          
          carry = sum/10;
      }
      return anshead;
  }

/*
// More Optimized add Function
  struct Node* add(struct Node* first, struct Node* second)
  {
      int carry = 0;
      Node* anshead = NULL;
      Node* anstail = NULL;
      
      while(first != NULL || second != NULL || carry != 0)
      {
          int val1 = 0;
          if(first != NULL)
            val1 = first -> data;
        
          int val2 = 0;
          if(second != NULL)
            val2 = second -> data;
          
          int sum = carry + val1 + val2;
          int digit = sum%10;
          
          //create node and add in answer list
          insertAtTail(anshead, anstail, digit);
          
          carry = sum/10;
          
          if(first != NULL)
              first = first -> next;
          if(second != NULL)
              second = second -> next;
      }
      
      return anshead;
  }
*/

    public:
    //Function to add two numbers represented by linked list.
    struct Node* addTwoLists(struct Node* first, struct Node* second)
    {
        //Step -1 : reverse the lists
        first = reverse(first);
        second = reverse(second);
        
        //Step-2: add 2 lists
        Node* ans = add(first, second);
        
        //Step-3: reverse ans
        ans = reverse(ans);
        
        return ans;
    }
};

//T.C. : O(N+M)
//S.C. : O(Max(N,M))

