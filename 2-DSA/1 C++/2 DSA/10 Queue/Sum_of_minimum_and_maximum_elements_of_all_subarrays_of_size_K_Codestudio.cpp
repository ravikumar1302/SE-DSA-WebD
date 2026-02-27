/*
Sum_of_minimum_and_maximum_elements_of_all_subarrays_of_size_K_Codestudio

Given an array of both positive and negative integers, the task is to compute sum of minimum and maximum elements of all sub-array of size k.
Examples: 
 

Input : arr[] = {2, 5, -1, 7, -3, -1, -2}  
        K = 4
Output : 18
Explanation : Subarrays of size 4 are : 
     {2, 5, -1, 7},   min + max = -1 + 7 = 6
     {5, -1, 7, -3},  min + max = -3 + 7 = 4      
     {-1, 7, -3, -1}, min + max = -3 + 7 = 4
     {7, -3, -1, -2}, min + max = -3 + 7 = 4   
     Sum of all min & max = 6 + 4 + 4 + 4 
                          = 18   
*/

//Method 1 (Simple) 
//Run two loops to generate all subarrays of size k and find maximum and minimum values. Finally, return sum of all maximum and minimum elements. 
//Time taken by this solution is O(n*k).

// Method 2 (Efficient using Dequeue) 

long long sumOfMaxAndMin(vector<int> &nums, int n, int k) {
	deque<long long int> maxi(k);
    deque<long long int> mini(k);

    //Addition of first k size window

    for(int i=0; i<k; i++) {

        while(!maxi.empty() && nums[maxi.back()] <= nums[i])
            maxi.pop_back();

        while(!mini.empty() && nums[mini.back()] >= nums[i])
            mini.pop_back();

        maxi.push_back(i);
        mini.push_back(i);
    }
    long long int ans = 0;

    ans += nums[maxi.front()] + nums[mini.front()];

    //remaining windows ko process karlo
    for(int i=k; i<n; i++) {
        //next window

        //removal
        while(!maxi.empty() && i - maxi.front() >=k) 
            maxi.pop_front();
        
        while(!mini.empty() && i - mini.front() >=k)
            mini.pop_front();

        //addition

        while(!maxi.empty() && nums[maxi.back()] <= nums[i])
            maxi.pop_back();

        while(!mini.empty() && nums[mini.back()] >= nums[i])
            mini.pop_back();

        maxi.push_back(i);
        mini.push_back(i);    

        ans += nums[maxi.front()] + nums[mini.front()];
    }
    return ans;
}

// T.C. : O(N)