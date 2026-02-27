/*
Intersection_Point_in_Y_Shapped_Linked_Lists_GFG

Given two singly linked lists of size N and M, write a program to get the point where two linked lists intersect each other.

    Example 1:

    Input:
    LinkList1 = 3->6->9->common
    LinkList2 = 10->common
    common = 15->30->NULL
    Output: 15
*/

int len(Node* head)
{
    int cnt = 0;
    while(head != NULL)
    {
        head = head -> next;
        cnt++;
    }
    return cnt;
}

int differ(Node* big, Node* small, int biglen, int small_len)
{
    int dif = biglen - small_len;
    while(dif)
    {
        big = big -> next;
        dif--;
    }
    while(big != NULL && small != NULL)
    {
        if(big == small)
            return big -> data;
        else
        {
            big = big -> next;
            small = small -> next;
        }
    }
    return -1;
}

int intersectPoint(Node* head1, Node* head2)
{
    int l1 = len(head1);
    int l2 = len(head2);
    
    if(l1 > l2)
        return differ(head1, head2, l1, l2);
    else
        return differ(head2, head1, l2, l1);
    
    return -1;
}


/*
// More clean code

int intersectPoint(Node* head1, Node* head2)
{
    if(head1 == NULL || head2 == NULL)
        return NULL;
    Node* a = head1;
    Node* b = head2;
    
    while(a != b)
    {
        a = (a == NULL) ? head2 : a -> next; 
        b = (b == NULL) ? head1 : b -> next;
    }
    return a ? a -> data : -1;
}

//T.C. : O(N)
//S.C. : O(N)
*/


/*
One more method: long

make one list loop and then use get starting node method
*/