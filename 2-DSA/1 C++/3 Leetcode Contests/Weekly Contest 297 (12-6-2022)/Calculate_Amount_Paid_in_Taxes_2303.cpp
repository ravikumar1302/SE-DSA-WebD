/*
5259. Calculate Amount Paid in Taxes

You are given a 0-indexed 2D integer array brackets where brackets[i] = [upperi, percenti] means that the ith tax bracket has an upper bound of upperi and is taxed at a rate of percenti. The brackets are sorted by upper bound (i.e. upperi-1 < upperi for 0 < i < brackets.length).

Tax is calculated as follows:

The first upper0 dollars earned are taxed at a rate of percent0.
The next upper1 - upper0 dollars earned are taxed at a rate of percent1.
The next upper2 - upper1 dollars earned are taxed at a rate of percent2.
And so on.
You are given an integer income representing the amount of money you earned. Return the amount of money that you have to pay in taxes. Answers within 10-5 of the actual answer will be accepted.

    Example 1:

    Input: brackets = [[3,50],[7,10],[12,25]], income = 10
    Output: 2.65000
    Explanation:
    The first 3 dollars you earn are taxed at 50%. You have to pay $3 * 50% = $1.50 dollars in taxes.
    The next 7 - 3 = 4 dollars you earn are taxed at 10%. You have to pay $4 * 10% = $0.40 dollars in taxes.
    The final 10 - 7 = 3 dollars you earn are taxed at 25%. You have to pay $3 * 25% = $0.75 dollars in taxes.
    You have to pay a total of $1.50 + $0.40 + $0.75 = $2.65 dollars in taxes.
*/

class Solution {
public:
    double calculateTax(vector<vector<int>>& brackets, int income) {
        double ans=0;  
        if(income==0){
            return ans;
        }
        int prev=0; 
        for(int i=0;i<brackets.size();i++)
        {
            int actual=min(brackets[i][0],income);
            ans+=((actual-prev)*brackets[i][1]*1.0)/100.0;
            if(brackets[i][0]>=income)
            {
                break;
            }
            prev=brackets[i][0];
        }
        return ans;
    }
};