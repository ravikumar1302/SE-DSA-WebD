/*
Minimum_no_of_jumps_GFG

Given an array of N integers arr[] where each element represents the max number of steps that can be made forward from that element. 
Find the minimum number of jumps to reach the end of the array (starting from the first element). 
If an element is 0, then you cannot move through that element.
Note: Return -1 if you can't reach the end of the array.
*/

class Solution{
  public:
    int minJumps(int arr[], int n){
        if (n <= 1)
        return 0;
 
        if (arr[0] == 0)
            return -1;
     
        int maxReach = arr[0];
        int step = arr[0];
        int jump = 1;
     
        int i = 1;
        for (i = 1; i < n; i++) {
            if (i == n - 1)
                return jump;
    
            maxReach = max(maxReach, i + arr[i]);
            step--;
            if (step == 0) {
                jump++;
                if (i >= maxReach)
                    return -1;
                step = maxReach - i;
            }
        }
     
        return -1;
    }
};