/*
Fractional_Knapsack_GFG

Given weights and values of N items, we need to put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
Note: Unlike 0/1 knapsack, you are allowed to break the item. 

    Example 1:
    Input: N = 3, W = 50, values[] = {60,100,120}, weight[] = {10,20,30}
    Output: 240.00
    Explanation:Total maximum value of item we can have is 240.00 from the given capacity of sack.

    Example 2:
    Input: N = 2, W = 50, values[] = {60,100}, weight[] = {10,20}
    Output: 160.00
    Explanation: Total maximum value of item we can have is 160.00 from the given capacity of sack.
 

Expected Time Complexity : O(NlogN)
Expected Auxilliary Space: O(1)
*/


// Time : O(NlogN) + O(N)       for sorting and iteration
// Space : O(1)

// Approach : Sort on basis of value/weight and then iterate

//class implemented
/*
struct Item{
    int value;
    int weight;
};
*/


class Solution
{
    public:
    static bool comp(Item a, Item b)
    {
        double r1 = (double)a.value / (double)a.weight;
        double r2 = (double)b.value / (double)b.weight;
        return r1 > r2;
    }
    
    //Function to get the maximum total value in the knapsack.
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        sort(arr, arr+n, comp);

        int  curWeight = 0;
        double finalvalue = 0.0;

        for(int i=0; i<n; i++)
        {
            if(curWeight + arr[i].weight <= W)
            {
                curWeight += arr[i].weight;
                finalvalue += arr[i].value;
            }
            else
            {
                // Adding fraction value
                
                int remain = W - curWeight;
                finalvalue += (arr[i].value / (double)arr[i].weight)*(double)remain;
                break;
            }
        }
        return finalvalue;
    }
        
};