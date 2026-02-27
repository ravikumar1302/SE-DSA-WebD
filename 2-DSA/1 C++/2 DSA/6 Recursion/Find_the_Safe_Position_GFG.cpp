/*
Find_the_Safe_Position_GFG

There are n people standing in a circle (numbered clockwise 1 to n) waiting to be executed. The counting begins at point 1 in the circle and proceeds around the circle in a fixed direction (clockwise). In each step, a certain number of people are skipped and the next person is executed. The elimination proceeds around the circle (which is becoming smaller and smaller as the executed people are removed), until only the last person remains, who is given freedom.
Given the total number of persons n and a number k which indicates that k-1 persons are skipped and kth person is killed in circle. The task is to choose the place in the initial circle so that you are the last one remaining and so survive.

    Example 1:
    Input : n = 2, k = 1
    Output : 2
    Explanation : Here, n = 2 and k = 1, then safe position is 2 as the person at 1st position will be killed.

Expected Time Complexity: O(n*n)
Expected Auxiliary Space: O(n)

Follow up: This problem can be solved in linear time. Can you come up with a solution?  : YES

*/

// Time : O(N)
// Space : O(N)

class Solution {
  public:
    int safePos(int n, int k) {
        vector<int> v;
        for(int i = 1; i<=n; i++)
            v.push_back(i);
        
        auto start = 0;
        while(n != 1)
        {
            int end = (start + k -1)%n;
            v.erase(v.begin() + end);
            
            n--;
            start = end;
        }
        return v[0];
    }
};


