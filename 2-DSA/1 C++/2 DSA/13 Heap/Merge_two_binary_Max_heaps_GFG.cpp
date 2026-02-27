/*
Merge_two_binary_Max_heaps_GFG

Given two binary max heaps as arrays, merge the given heaps to form a new max heap.

    Example 1:

    Input  : 
    n = 4 m = 3
    a[] = {10, 5, 6, 2}, 
    b[] = {12, 7, 9}
    Output : 
    {12, 10, 9, 2, 5, 7, 6}

Expected Time Complexity: O(n.Logn)
Expected Auxiliary Space: O(n + m)

*/

// Using STL

class Solution{
    public:
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
        
        priority_queue<int> pq;
        
        for(int i=0; i<n; i++)
            pq.push(a[i]);
        for(int i=0; i<m; i++)
            pq.push(b[i]);
        
        vector<int> ans;
        while(!pq.empty())
            {
                ans.push_back(pq.top() );
                pq.pop();
            }
        return ans;
    }
};


// Approach 2

class Solution{
    public:
    
void heapify (vector<int> &arr, int n, int i)
{
    //0 based indexing
    int largest = i;    
    int left = 2*i +1;
    int right = 2*i + 2;

    if(left < n && arr[largest] < arr[left])
        largest = left;

    if(right < n && arr[largest] < arr[right])
        largest = right;

    if(largest != i)
    {
        swap(arr[largest], arr[i]);
        heapify(arr, n, largest);
    }
}
    
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
        
        // S1 : merge two arrays
        vector<int> ans;
        
        for(auto i : a)
            ans.push_back(i);
            
        for(auto i : b)
            ans.push_back(i);
        
        // S2 : Create heap
        int size = ans.size();
        
        for(int i = size/2 -1; i>=0; i--)  // for loop and heapify together takes overall O(N) time
            heapify(ans, size ,i);
            
        return ans;
    }
};