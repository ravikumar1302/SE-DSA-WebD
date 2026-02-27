/*
Duplicate_in_an_array_Codestudio

You are given an array ‘ARR’ of size ‘N’ containing each number between 1 and ‘N’ - 1 at least once. 
There is a single integer value that is present in the array twice. 
Your task is to find the duplicate integer value present in the array.
*/

#include<algorithm>
#include<bits/stdc++.h>
int findDuplicate(vector<int> &arr) 
{
    // Write your code here
	int ans = 0;
	for(int i = 0; i < arr.size(); i++) 
	{
       ans = ans^arr[i];
       ans = ans^i;
  	}
   return ans;
}
