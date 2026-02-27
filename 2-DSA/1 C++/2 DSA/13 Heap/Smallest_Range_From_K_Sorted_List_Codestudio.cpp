/*
Smallest_Range_From_K_Sorted_List_Codestudio

You are given ‘K’ lists containing non-negative integers. Each list has a size ‘N’ and is sorted in non-decreasing order. 
You need to find the minimum length of a range such that at least one element of each list must be included in that range.

For example :
If we have 3 lists as [1, 10, 11], [2, 3, 20], [5, 6, 12] then the [1, 5] is the range that includes 1 from the first list, 2,3 from the second list, and 5 from the third list i.e, this range contains at least one element from each list.

    Sample Input 1 :
    2
    3 2
    2 4 5
    5 6 7
    2 3
    1 1
    9 12
    4 9

    Sample Output 1 :
    1
    9

    Explanation For Sample Input 1 :
    Test case 1 :
    The given list are [2, 4, 5], [5, 6, 7]. The range [5, 5] will include 5 which is present in both the list and hence the length of this range is 1. This is the only possible range having the minimum length.

    Test case 2 :
    The given list are [1, 1], [9, 12], [4, 9]. The range [1, 9] will include 1 which is present in the first list, and 9 which include in both the second and third list  The length of the range is 9 (9 - 1 + 1 = 9).

*/

// Brute force approach : Go to each element and check range for every element : Time : O( (N*K)^2 )

// Optimized Approach : 
// Time : O(N*k*k)
// Space : O(k)

// Storing first elemment of each sorted vector in a heap, and have a pointer at smallest and largest value
// You already have one range now, for small ans, the smalest value in its row, and every time check the smallest and largest in that 1sr element vector and see if it's samll or not

#include<limits.h>
#include<queue>
class node
{
    public:
    int data;
    int row;
    int col;
    
    node(int d, int r, int c)
    {
        data = d;
        row = r;
        col = c;
    }
};

class compare
{
    public:
    bool operator() (node* a, node* b)
    {
        return a->data > b->data;
    }
};

int kSorted(vector<vector<int>> &a, int k, int n) {
    
    // Step 1 : Find minimum and maximum from 1st element and it's rows, Time : O(K)
    priority_queue<node*, vector<node*>, compare > minheap;
    int mini = INT_MAX;
    int maxi = INT_MIN;
    
    for(int i=0; i<k; i++)
    {
        int element = a[i][0];
        mini = min(mini, element);
        maxi = max(maxi, element);
        minheap.push(new node(element, i, 0) );    
    }
    
    int start = mini, end = maxi;
    
    // Step 2  : Processing ranges
    while(!minheap.empty())
    {
        // mini fetch
        node* temp =  minheap.top();
        minheap.pop();
        
        mini = temp->data;
        
        // range or ansawer update
        if(maxi-mini < end-start)
        {
            start = mini;
            end = maxi;
        }
        
        // next element exists
        if(temp->col + 1 < n)
        {
            maxi = max(maxi, a[temp->row][temp->col + 1]);
            minheap.push(new node( a[temp->row][temp->col + 1], temp->row, temp->col + 1 ));
        }
        // next element does not exists
        else
            break;
    }
    return (end - start + 1);
    
}