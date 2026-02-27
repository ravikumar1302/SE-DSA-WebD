/*
Rotate Array GFG
Quick Left Rotation GFG
Rotate Array Leetcode_189 : Right shift
Left Rotate an Array by One_Codestudio

Given an unsorted array arr[] of size N. Rotate the array to the left (counter-clockwise direction) by D steps, where D is a positive integer.

Example 1:
Input : N = 5, D = 2, arr[] = {1,2,3,4,5}
Output: 3 4 5 1 2
Explanation: 1 2 3 4 5  when rotated by 2 elements, it becomes 3 4 5 1 2.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/

class Solution
{
public:
    // Function to rotate an array by d elements in counter-clockwise direction.
    void rotateArr(int arr[], int d, int n)
    {

        // Edge case : if d > n
        d = d % n;

        // Try this method on Pen-Paper
        reverse(arr + 0, arr + d);
        reverse(arr + d, arr + n);
        reverse(arr + 0, arr + n);
    }
};

// Above code are for left shift

// To right shift, code is

void rotate(vector<int> &nums, int k)
{

    int n = nums.size();
    int d = k;
    d = d % n;

    d = n - d; // The only diffrence from above code (which left-shifts) switching remaning terms left = switching k terms by right

    // Try this method on Pen-Paper
    reverse(nums.begin() + 0, nums.begin() + d);
    reverse(nums.begin() + d, nums.begin() + n);
    reverse(nums.begin() + 0, nums.begin() + n);
}

// Approach-2

void rotate(vector<int> &nums, int k)
{
    vector<int> temp(nums.size());
    for (int i = 0; i < nums.size(); i++)
    {
        temp[(i + k) % nums.size()] = nums[i];
    }
    nums = temp;
}

// For only one left shift
vector<int> rotateArray(vector<int> &arr, int n)
{
    // Write your code here.

    int first = arr[0];
    for (int i = 0; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[n - 1] = first;

    return arr;
}
