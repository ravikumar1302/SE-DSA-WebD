/*
Alternate_positive_and_negative_numbers_GFG

Given an unsorted array Arr of N positive and negative numbers. Your task is to create an array of alternate positive and negative numbers without changing the relative order of positive and negative numbers.
Note: Array should start with positive number.

	Example 1:
	Input:
	N = 9, Arr[] = {9, 4, -2, -1, 5, 0, -5, -3, 2}
	Output: 9 -2 4 -1 5 -5 0 -3 2

	Example 2:
	Input: N = 10, Arr[] = {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8}
	Output: 5 -5 2 -2 4 -8 7 1 8 0

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(N)
*/

// Method-1 : Storing positive and negative no in separate array

class Solution
{
public:
	void rearrange(int arr[], int n)
	{

		vector<int> pos;
		vector<int> neg;

		for (int i = 0; i < n; i++)
		{
			if (arr[i] < 0)
				neg.push_back(arr[i]);
			else
				pos.push_back(arr[i]);
		}

		int j = 0, k = 0, i = 0;
		while (i < n)
		{
			if (j < pos.size())
				arr[i++] = pos[j++];
			if (k < neg.size())
				arr[i++] = neg[k++];
		}
	}
};

// Solution-2

class Solution
{
public:
	void rearrange(int arr[], int n)
	{

		vector<int> pos;
		vector<int> neg;

		for (int i = 0; i < n; i++)
		{
			if (arr[i] < 0)
				neg.push_back(arr[i]);
			else
				pos.push_back(arr[i]);
		}

		int i = 0, j = 0, k = 0;
		bool flag = true; // Without flag, and keeping other thing exactly same, also gives correct ans
		while (i < pos.size() || j < neg.size())
		{
			if (flag == true && i < pos.size())
			{
				arr[k] = pos[i];
				i++;
				k++;
			}

			if (flag == false && j < neg.size())
			{
				arr[k] = neg[j];
				j++;
				k++;
			}
			flag = !flag;
		}
	}
};