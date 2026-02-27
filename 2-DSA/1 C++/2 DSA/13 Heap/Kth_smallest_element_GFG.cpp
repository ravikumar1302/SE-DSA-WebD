/*
Kth_smallest_element_GFG

Given an array arr[] and an integer K where K is smaller than size of array, the task is to find the Kth smallest element in the given array. It is given that all array elements are distinct.

    Example 1:

    Input:
    N = 6
    arr[] = 7 10 4 3 20 15
    K = 3
    Output : 7
    Explanation :
    3rd smallest element in the given 
    array is 7

Expected Time Complexity: O(n)
Expected Auxiliary Space: O(log(n))

*/

/*
Approach 1 : O(NlogN) time
    a) sort the function in increasing order O(NlogN)
    b) return arr[k-1]
*/

/* 
Approach 2 :  Using heap and with O(NlogN) time
    a) for first k (0 to k-1) elements, create a max heap
    b) for rest (k to n-1) elements, check if element < heap.top(), if yes then
            heap.pop()
            heap.push(element)
    so, after complete run, heap will have k elemetns, ans heap,top() will give the answer
*/

class Solution{
    public:
    // arr : given array
    // l : starting index of the array i.e 0
    // r : ending index of the array i.e size-1
    // k : find kth smallest element and return using this function
    int kthSmallest(int arr[], int l, int r, int k) {
        
        // Step-1 : for first k (0 to k-1) elements, create a max heap 
        priority_queue<int> pq;
        
        for(int i=0; i<k; i++)
            pq.push(arr[i]);
        
        // Step-1 : for rest (k to n-1) elements, check if element < heap.top(), if yes then heap.pop() and heap.push(element)
        for( int i=k; i<=r; i++)
        {
            if(arr[i] < pq.top())
            {
                pq.pop();
                pq.push(arr[i]);
            }
        }
        
        int ans = pq.top();
        return ans;
    }
};