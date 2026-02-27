// Basic Functions of Heap

// We will be using array to implement heap

#include<iostream>
#include<queue>
using namespace std;

class heap{
    public:
    int arr[100];
    int size;

    heap()
    {
        arr[0] = -1;
        size = 0;
    }

    void insert(int val) {

        //initially adding element in last
        size = size + 1;
        int index = size;
        arr[index] = val;

        // Putting the new element at right place
        while(index >1)
        {
            int parent = index/2;

            if(arr[parent] < arr[index])
            {
                swap(arr[parent], arr[index]);
                index = parent;
            }
            else
                return;
        }
    }

    void print()
    {
        for(int i=1; i<=size; i++)
            cout<<arr[i]<<" ";
        cout<<endl;
    }

    void deleteFromHeap()   // Time O(logN)
    {
        //Deletion occor at root node in heap
        if(size == 0)
        {
            cout<<"Nothing to delete"<<endl;
            return;
        }
        
        // Step 1 : to delete root elemet, make root element value as last node value : O(1)
        arr[1] = arr[size];

        // Step 2: remove last element : O(1)
        size--;

        // Step 3 : take root node to it's right position : O(logN)
        int i = 1;
        while(i < size)
        {
            int leftIndex = 2*i;
            int rightIndex = 2*i + 1;

            if(leftIndex < size && arr[i] < arr[leftIndex])
                {
                    swap(arr[i], arr[leftIndex]);
                    i = leftIndex;
                }
            else if(rightIndex < size && arr[i] < arr[rightIndex])
            {
                    swap(arr[i], arr[rightIndex]);
                    i = rightIndex;
            }
            else
                return;
        }
    }
};


    // In 0 based indexing
    // left is 2*i +1 (not 2*i)
    // right is 2*i +2 (not 2*i+1)

// HEAPIFY ALGORITHM :  O(logN) time
void heapify (int arr[], int n, int i)
{
    // If not given we use 1 based indexing
    int largest = i;    // As it is max heap
    int left = 2*i;
    int right = 2*i + 1;

    if(left <= n && arr[largest] < arr[left])
        largest = left;

    if(right <= n && arr[largest] < arr[right])
        largest = right;

    if(largest != i)
    {
        swap(arr[largest], arr[i]);
        heapify(arr, n, largest);
    }
}

// This sorting take O(NlogN) time
void heapSort(int arr[], int n)
{
    int t = n;

    while(t > 1)
    {
        // Step 1 : swap first and last element, as top element will be largest
        swap(arr[t], arr[1]);
        // Step 2 : decrement the size
        t--;
        // Step 3 : Heapyfy the root node, so that reamning largest element comes to top
        heapify(arr, t, 1);;
    }
}

int main() {

    heap h;
    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.insert(52);
    h.insert(54);
    h.print();

    h.deleteFromHeap();
    h.print();

    int arr[6] = {-1, 54, 53, 55, 52, 50};
    int n =5;   //size of upper array excluding 0 index


    // For 0 based indexing, go from (n/2 -1) to 0
    // The area we are traversing are the non-leaf nodes, as leaf nodes are already considered to be a heap
    // Creaing heap
    for(int i = n/2; i>0; i--)  // for loop and heapify together takes overall O(N) time
        heapify(arr, n,i);

    cout<<endl<<"Printing the array after heapify algo : "<<endl;
    for(int i=1; i<=n; i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    // Heap Sort
    heapSort(arr, n);

    cout<<endl<<"Heap sort Array : "<<endl;
    for(int i=1; i<=n; i++)
        cout<<arr[i]<<" ";
    cout<<endl;


    cout<<endl<<"Using priority queue here : "<<endl;
    
    // Max-heap
    priority_queue<int> pq;

    pq.push(4);
    pq.push(2);
    pq.push(5);
    pq.push(3);

    cout<<"element at top "<<pq.top()<<endl;
    pq.pop();
    cout<<"element at top "<<pq.top()<<endl;
    cout<<"Size is "<<pq.size()<<endl;

    if(pq.empty())
        cout<<"it is empty"<<endl;
    else
        cout<<"It's not empty"<<endl;
    
    // Min heap
    cout<<endl<<"Min heap"<<endl;
    priority_queue<int, vector<int>, greater<int> > minheap;
    minheap.push(4);
    minheap.push(2);
    minheap.push(5);
    minheap.push(3);  

    cout<<"element at top "<<minheap.top()<<endl;
    minheap.pop();
    cout<<"element at top "<<minheap.top()<<endl;
    cout<<"Size is "<<minheap.size()<<endl;

    if(minheap.empty())
        cout<<"it is empty"<<endl;
    else
        cout<<"It's not empty"<<endl;  

    return 0;
}