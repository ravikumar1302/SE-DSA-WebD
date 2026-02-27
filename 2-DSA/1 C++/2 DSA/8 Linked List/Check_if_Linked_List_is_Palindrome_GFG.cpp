/*
Check_if_Linked_List_is_Palindrome_GFG
Palindrome Linked List Leetcode_234

Given a singly linked list of size N of integers. The task is to check if the given linked list is palindrome or not.

    Example 1:

    Input : N = 3, value[] = {1,2,1}
    Output: 1
    Explanation: The given linked list is 1 2 1 , which is a palindrome and Hence, the output is 1.
*/

/*
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};
*/


//Approach : 1: in O(N) space, by taking a vector and adding all element of LL in vector and applying palindrome function on vector

#include<vector>
class Solution{
  private:
  bool checkpalindrome(vector<int> arr)
  {
      int s = 0;
      int e = arr.size() -1;
      while(s <= e)
      {
          if(arr[s] != arr[e])
            return 0;
            else
            {
                s++;
                e--;
            }
            
      }
      return 1;
  }
  public:
    //Function to check whether the list is palindrome.

    //Approach : 1: in O(N) space, by taking a vector and adding all element of LL in vector and applying palindrome function on vector
    bool isPalindrome(Node *head)
    {
        vector<int> arr;
        Node* temp = head;
        while(temp != NULL)
        {
            arr.push_back(temp -> data);
            temp = temp -> next;
        }
        return checkpalindrome(arr);
    }
};
// T.C. : O(N)
// S.C. : O(N)

/*****************************************************************************************/

//Method -2 (Optimized)
// Step 1 : find mid
// Step 2 : reverse right half
// Step 3 : compare left and right half
// Step 4 : reverse right half again to make LL as original
// Step 5 : return ans

class Solution{
  private:
  
  Node* getmid(Node* head)
  {
      Node* slow = head;
      Node* fast = head -> next;
      while(fast != NULL && fast -> next != NULL)
      {
          fast = fast -> next -> next;
          slow = slow -> next;
      }
      return slow;
  }
  
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
  
  public:
    //Function to check whether the list is palindrome.
    bool isPalindrome(Node *head)
    {
        if(head -> next == NULL)
            return true;
        
        //Step -1 : get mid
        Node* middle = getmid(head);
        
        //Step -2: reverse righthalf
        Node* temp = middle -> next;
        middle -> next = reverse(temp);
        
        // Comare both halves
        Node* head1 = head;
        Node* head2 = middle -> next;
        
        while(head2 != NULL)
        {
            if(head1 -> data != head2 -> data)
                return false;
            head1 = head1 -> next;
            head2 = head2 -> next;
        }
        
        //Step-4 repeat step 2 (to make original list as it is)
        temp = middle -> next;
        middle -> next = reverse(temp);
        
        return true;
    }
};

// T.C. : O(N)
// S.C. : O(1)