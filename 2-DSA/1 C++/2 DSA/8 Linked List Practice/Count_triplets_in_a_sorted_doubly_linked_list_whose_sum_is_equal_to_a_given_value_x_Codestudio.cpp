/*
Count_triplets_in_a_sorted_doubly_linked_list_whose_sum_is_equal_to_a_given_value_x_Codestudio

You are given a sorted doubly linked list of distinct nodes that means no two nodes present in the list have the same data. You are also given an integer 'X'.Your task is to count the number of triplets in the list that sum up to a given value 'X'.
A doubly linked List (DLL) contains an extra pointer, called the previous pointer, together with the next pointer and data, which are there in the singly linked list such that both forward and backward navigation is possible.
For example, DLL is 1<->2<->3<->4 NULL and the given integer 'X' is 9, then the number of triplets having the sum 9 is only one, and that is (2,3,4).

    Sample Input 1 :
    3
    1 2 3 8 9 -1
    13
    1 2 3 4 5 6 7 8 9 -1
    15
    7 33 88 91 -1
    40
    Sample Output 1 :
    2
    8
    0
    Explanation Of The Sample Input 1:
    For the first test case:
    The linked List is 1<-->2<-->3<-->8<-->9 NULL
    We can clearly see that 2 triplets exist for this case, i.e., (2,3,8) and (1,3,9)

    For the second test case:
    The linked List is :1<-->2<-->3<-->4←>5<-->6<-->7<-->8<-->9 NULL
    For this case we can see that there are total of eight triplets i.e. (2,4,9),(4,5,6),(2,6,7),(3,4,8),(1,5,9),(1,6,8),(2,5,8)and (3,5,7)

    For the third test case:
    The Linked List is 7<-->33<-->88<-->91 NULL
    For this test case, we can see that there is no such triplet that gives us the 40, so the answer will be zero here.
*/

/***********************************************

    Following is the class structure of the Node class:

    class DLLNode
    {
        public:
        int data;
        DLLNode *next;
        DLLNode *prev;
    };

***********************************************/

int countTriplets(DLLNode* head, int x)
{
    int ans = 0;
    DLLNode* last = head;
    while(last -> next != NULL)
            last = last -> next;
    
    while(head -> next -> next != NULL)
    {
        int v1 = head -> data;
        
        DLLNode* fwd = head -> next;
        DLLNode* temp = last;
        
        while(fwd != temp && !(temp -> next == fwd || fwd-> prev == temp) )
        {
            if(v1 + fwd -> data + temp -> data == x)
            {
                ans++;
                fwd = fwd -> next;
                temp = temp -> prev;
            }
            else if(v1 + fwd -> data + temp -> data < x)
                fwd = fwd -> next;
            else if(v1 + fwd -> data + temp -> data > x)
                temp = temp -> prev;
        }
        head = head -> next;
    }
    return ans;
}  

// T.C. : O(N^2)
// S.C. : O(1)