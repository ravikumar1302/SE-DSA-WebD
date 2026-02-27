/*
Job_Sequencing_Problem
Not able to open the ques on GFG, Server issue

Given an array of jobs where every job has a deadline and associated profit if the job is finished before the deadline. It is also given that every job takes a single unit of time, so the minimum possible deadline for any job is 1. Maximize the total profit if only one job can be scheduled at a time.

    Examples: 
    Input: Four Jobs with following deadlines and profits

    JobID  Deadline  Profit
    a          4          20   
    b          1          10
    c          1          40  
    d          1          30
    Output: Following is maximum profit sequence of jobs: c, a   

    Input:  Five Jobs with following deadlines and profits

    JobID   Deadline  Profit
    a            2          100
    b            1          19
    c            2          27
    d            1          25
    e            3          15  
    Output: Following is maximum profit sequence of jobs: c, a, e
    
    Example 1:
    Input: N = 4, Jobs = {(1,4,20),(2,1,10),(3,1,40),(4,1,30)}
    Output: 2 60
    Explanation: The 3rd job with a deadline 1 is performed during the first unit of time .The 1st job is performed during the second unit of time as its deadline is 4. Profit = 40 + 20 = 60

    Example 2:
    Input: N = 5, Jobs = {(1,2,100),(2,1,19),(3,2,27),(4,1,25),(5,1,15)}
    Output: 2 127
    Explanation: The  first and third job both having a deadline 2 give the highest profit. Profit = 100 + 27 = 127

*/


/*
Stiver Approach

Approach:  The strategy to maximize profit should be to pick up jobs that offer higher profits. Hence we should sort the jobs in descending order of profit. 
Now say if a job has a deadline of 4 we can perform it anytime between day 1-4, but it is preferable to perform the job on its last day. This leaves enough empty slots on the previous days to perform other jobs.
Basic Outline of the approach:-
    Sort the jobs in descending order of profit. 
    If the maximum deadline is x, make an array of size x .Each array index is set to -1 initially as no jobs have been performed yet.
    For every job check if it can be performed on its last day.
    If possible mark that index with the job id and add the profit to our answer. 
    If not possible, loop through the previous indexes until an empty slot is found.
*/

// Striver Solution
bool comparison(Job a, Job b)
{
     return (a.profit > b.profit);
}

pair<int, int> printJobScheduling(Job arr[], int n)
{
    sort(arr, arr+n, comparison);
    int maxi = arr[0].dead;
    for(int i=1; i<n; i++)
        maxi = max(maxi, arr[i].dead);
    
    int slot[maxi + 1];
    for(int i=0; i<=maxi; i++)
        slot[i] = -1;
    
    int countJobs = 0, jobProfit = 0;
    for (int i=0; i<n; i++)
    {
       for (int j= arr[i].dead; j>0; j--)
       {
            if(slot[j] == -1)
            {
                slot[j] = i;
                countJobs++;
                jobProfit += arr[i].profit;
                break;
            }
       }
    }
    return make_pair(countJobs, jobProfit);
}




// InterviewBit Solution

/*
Approach 1: Greedy Algorithm (Since, the task is to get the maximum profit by scheduling the jobs, the idea is to approach this problem greedily )
Algorithm
    1. Sort the jobs based on decreasing order of profit.
    2. Iterate through the jobs and perform the following:
        2.1 Choose a Slot i if:
            Slot i isn’t previously selected.
            I < deadline    
            I is maximum
        2.2 If no such slot exists, ignore the job and continue.
*/


struct Job
{
   char id;     
   int dead;  
   int profit; 
};
bool comparison(Job a, Job b)
{
     return (a.profit > b.profit);
}
void printJobScheduling(Job arr[], int n)
{
    sort(arr, arr+n, comparison);
  
    int result[n];
    bool slot[n];
    for (int i=0; i<n; i++)
        slot[i] = false;
 
    for (int i=0; i<n; i++)
    {
       for (int j=min(n, arr[i].dead)-1; j>=0; j--)
       {
          if (slot[j]==false)
          {
             result[j] = i;  
             slot[j] = true;
             break;
          }
       }
    }
    for (int i=0; i<n; i++)
       if (slot[i])
         cout << arr[result[i]].id << " ";
}

// Time : O(NlogN) + O(N*M), where m is the maximum deadline     // sorting and iteration
// Space : O(M)     // slot array