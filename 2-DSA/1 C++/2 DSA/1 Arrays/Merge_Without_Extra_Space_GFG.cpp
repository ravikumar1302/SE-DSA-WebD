/*
Merge_Without_Extra_Space_GFG

Given two sorted arrays arr1[] of size N and arr2[] of size M. 
Each array is sorted in non-decreasing order. 
Merge the two arrays into one sorted array in non-decreasing order without using any extra space.
*/

class Solution{
public:
	void merge(int arr1[], int arr2[], int n, int m) {
	    int a1 = n-1, a2 = 0;
       while(a1>=0 && a2<m){
           if(arr1[a1] > arr2[a2]){
               swap(arr1[a1],arr2[a2]);
               a1--;
               a2++;
           }
           else
               break;
       }
       sort(arr1,arr1+n);
       sort(arr2,arr2+m);
	}
};