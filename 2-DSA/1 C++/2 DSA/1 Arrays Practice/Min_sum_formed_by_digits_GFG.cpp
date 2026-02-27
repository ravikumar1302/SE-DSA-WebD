/*
Min_sum_formed_by_digits_GFG

Given an array of digits (values are from 0 to 9), find the minimum possible sum of two numbers formed from digits of the array. All digits of given array must be used to form the two numbers.

    Example 1:
    Input: N = 6, arr[] = {6, 8, 4, 5, 2, 3}
    Output : 604
    Explanation : The minimum sum is formed by numbers 358 and 246

Expected Time Complexity: O(N. log(N))
Expected Auxiliary Space: O(1)
*/

/* Approach
A minimum number will be formed from set of digits when smallest digit appears at most significant position and next smallest digit appears at next most significant position ans so on..
The idea is to sort the array in increasing order and build two numbers by alternating picking digits from the array. 
So first number is formed by digits present in odd positions in the array and second number is formed by digits from even positions in the array. Finally, we return the sum of first and second number.
*/

// For very large numbers, we use strings to handle the question


string solve(int arr[], int n)
{
	sort(arr, arr + n);     // O(nlogn)
	string a = "", b = "";

	for (int i = 0; i < n; i += 2)
		a += (arr[i] + '0');

	for (int i = 1; i < n; i += 2)
	    b += (arr[i] + '0');

	int j = a.length() - 1;
	int k = b.length() - 1;

	int carry = 0;
	string ans = "";
	while (j >= 0 && k >= 0)
	{
		int sum = 0;
		sum += (a[j] - '0') + (b[k] - '0') + carry;
		ans += to_string(sum % 10);
		carry = sum / 10;
		j--;
		k--;
	}
	// if string b is over and string a is left
	// here we dont need to put here while condition as it would run at max one time. Because the difference between both the strings could be at max 1.
	while (j >= 0)
	{
		int sum = 0;
		sum += (a[j] - '0') + carry;
		ans += to_string(sum % 10);
		carry = sum / 10;
		j--;
	}
	// if string a is over and string b is left
	while (k >= 0)
	{
		int sum = 0;
		sum += (b[k] - '0') + carry;
		ans += to_string(sum % 10);
		carry = sum / 10;
		k--;
	}
	// if carry is left
	if (carry)
	{
		ans += to_string(carry);
	}
	// to remove leading zeroes as they will be ahead of our sum
	while (!ans.empty() and ans.back() == '0')
		ans.pop_back();
	// reverse our final string because we were storing sum from left to right
	reverse(ans.begin(), ans.end());
	return ans;
}


