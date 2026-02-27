/*
Farthest Number

Given an array Arr[] of size N. For every element in the array, the task is to find the index of the farthest element in the array to the right which is smaller than the current element. If no such number exists then print -1.
Note: 0 based indexing.

    Example 1:
    Input: N=5, Arr[] = {3, 1, 5, 2, 4}
    Output: 3 -1 4 -1 -1
    Explanation: Arr[3] is the farthest smallest element to the right of Arr[0]. 
    Arr[4] is the farthest smallest element to the right of Arr[2]. And for the rest of the elements, there is no smaller element to their right.

    Example 2:
    Input: N=5, Arr[] = {1, 2, 3, 4, 0}
    Output: 4 4 4 4 -1

Expected Time Complexity: O(N*logN)
Expected Auxiliary Space: O(N)
*/

// Not done in Test
// Using 1 vector

class Solution {
  public:
  int solve(vector<int> &temp, vector<int> &A, int curr)
  {
        int ans = 1;
        vector<int> :: iterator it;
        
        for(int i=2; i<temp.size() -1; i++)
        {
            it = find( A.begin(), A.end(),  4);
        }
        
        return ans;
  }
  
    vector<int> farNumber(int N, vector<int> &A) {
        
        //stack<int> s;
        //s.push(-1);
        vector<int> temp;
        temp.push_back(-1);
        temp.push_back(1000000009);
        
        vector<int> ans(N);
        
        vector<int> :: iterator it;
        
        for(int i=N-1; i>=0; i--)
        {
            int curr = A[i];
            
            // Smaller Element Found
            if(curr >= temp[1])
            {
                int dummy = solve(temp, A, curr);
                int index = find( A.begin(), A.end(),  temp[dummy]) - A.begin();
                ans[i] = index;
            }
            // Smaller element not found
            else
            {
                ans[i] = -1;
            }
            
            // To enter in vector find position and enter
            it = lower_bound(temp.begin(), temp.end(), curr);
            int index = it - temp.begin();
            if(temp[index] == 1000000009)
                temp.insert(index-1, curr);
            else
                temp.insert(index, curr);
        }
        
        return ans;
    }
};


// Using 1-Stack, but need many changes

class Solution {
  public:
  
    vector<int> farNumber(int N, vector<int> &A) {
        
        //stack<int> s;
        //s.push(-1);
        vector<int> temp;
        temp.push_back(-1);
        temp.push_back(1000000009);
        
        vector<int> ans(N);
        
        vector<int> :: iterator it;
        
        for(int i=N-1; i>=0; i--)
        {
            int curr = A[i];
            
            
            while(curr <= s.top())
                s.pop();
            
            // Now s.top() is smaller than curr
            it = find( A.begin(), A.end(), s.top() );
            if(it != A.end())
            {
               int index = it - A.begin();
               ans[i] = index;
            }
            else
                ans[i] = -1;
        
            s.push(curr);
            
            
            
        }
        
        return ans;
    }
};