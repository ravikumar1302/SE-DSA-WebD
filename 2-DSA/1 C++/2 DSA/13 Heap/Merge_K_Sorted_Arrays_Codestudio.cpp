/*
Merge_K_Sorted_Arrays_Codestudio

You have been given ‘K’ different arrays/lists, which are sorted individually (in ascending order). You need to merge all the given arrays/list such that the output array/list should be sorted in ascending order.
    
    Sample Input 1:
    1
    2
    3 
    3 5 9 
    4 
    1 2 3 8   
    Sample Output 1:
    1 2 3 3 5 8 9 
    Explanation Of Sample Input 1:
    After merging the two given arrays/lists [3, 5, 9] and [ 1, 2, 3, 8], the output sorted array will be [1, 2, 3, 3, 5, 8, 9].

*/

#include<queue>
vector<int> mergeKSortedArrays(vector<vector<int>>&kArrays, int k)
{
    priority_queue<int, vector<int>, greater<int> > ans;
    for(auto i : kArrays)
        for(auto j : i)
            ans.push(j);
    
    vector<int> ans2;
    while(!ans.empty())
    {
        ans2.push_back(ans.top());
        ans.pop();
    }
    return ans2;
}
// Insertion of element takes logN time, let say total vector have N elements and there are k such vectors
// Time : O(N*k*log(N*k) )
// Space : O(N*k)


/************************************************************************************************/

// Approach 2 : As all sub vectors are sorted, us that to optimize the solution
// Time : O(N*k*log(k) )    // as it's 'k' sized heap
// Space : O(N*k)
/*
    create a min heap to store the first element of each vector
    enter the array represented by that minheap top, and then pop it and add next element array if present
*/

#include<queue>
class node
{
    public:
    int data;
    int row;
    int col;
    
    node(int data, int row, int col)
    {
        this->data = data;
        this->row = row;
        this->col = col;
    }
};

class compare
{
    // Compare because of our custom made data structure, user have to make custom made compare function also
    public:
    bool operator() (node* a, node* b)
    {
        return (a->data > b->data);
    }
};

vector<int> mergeKSortedArrays(vector<vector<int>>&kArrays, int k)
{
    priority_queue<node*, vector<node*>, compare > minheap;    
    
    // S1 : Insert first element of all vectors in minheap
    // Time : O(KlogK)
    for(int i=0; i<k; i++)
    {
        node* temp = new node(kArrays[i][0], i, 0);
        minheap.push(temp);
    }
    
    vector<int> ans;
    
    // S2 : 
    while(minheap.size() > 0)
    {
        node* temp = minheap.top();
        
        ans.push_back(temp->data);
        minheap.pop();
        
        int row = temp -> row;
        int col = temp -> col;
        
        if(col+1 < kArrays[row].size())
        {
            node* next = new node(kArrays[row][col+1], row, col+1);
            minheap.push(next);
        }
    }
    
    return ans;
}