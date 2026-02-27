/*
Plus_one_GFG
Plus_one_Leetcode_66

Given a non-negative number represented as a list of digits, add 1 to the number (increment the number represented by the digits). 
The digits are stored such that the most significant digit is first element of array.
 
    Example 1:
    Input: N = 3, arr[] = {1, 2, 4}
    Output: 1 2 5
    Explanation: 124+1 = 125, and so the Output

    Example 2:
    Input: N = 3, arr[] = {9,9,9}
    Output: 1 0 0 0
    Explanation: 999+1 = 1000, and so the output

Expected Time Complexity:  O(N)
Expected Auxilliary Space: O(1)
*/


// Method-1

class Solution {
  public:
    vector<int> increment(vector<int> arr ,int N) 
    {
       for(int i=(N-1); i>=0; i--)
       {
           if(arr[i]!=9)
           {
               arr[i]=arr[i]+1;
               break;
           }
           else     // means arr[i] == 9
               arr[i]=0;
       }

       if(arr[0]==0)        // for numbers like 99, 999 etc..
       {
           arr.push_back(0);
           arr[0]=1;
       }
       return arr;
       
    }
};


// Method-2

class Solution {
  public:
    vector<int> increment(vector<int> arr ,int N) {
        
        arr.back() += 1;
        for (auto i = N-1; i > 0; i--) 
        {
            if (arr.at(i) == 10) 
            {
                arr.at(i) = 0;
                arr.at(i - 1) += 1;
            }
        }
        if (arr.front() == 10) 
        {
            arr.insert(arr.begin(), 1);
            arr.at(1) = 0;
        }
        return arr;
    }
};