/*
Three_way_split_Codestudio

Love Babber Contest 1 Question

Ninja has an array 'ARR' consisting of 'N' integers. Your primary work is to split it into three parts so that each integer is a component of a single part only.
Each part must be a consecutive contiguous subsegment of the original array and can also be empty. So, the sum of each part is denoted as 'S1', 'S2' and 'S3'.
Ninja made the problem even harder by declaring a condition that 'S1' must be equal to 'S3' and 'S1' must be the maximum possible amongst all possible ways.
The sum of the empty subsegment is 0.
*/

long long threeWaySplit(int n, vector<int> arr)
{
    if (n == 1)
        return 0;
    int i = 0, j = arr.size() - 1;
    int sum1 = 0, sum3 = 0;
    int ans = 0;
    while (i < j)
    {
        if (sum1 < sum3)
        {
            sum1 += arr[i++];
        }
        else if (sum1 > sum3)
        {
            sum3 += arr[j--];
        }
        else
        {
            ans = sum1;
            sum1 += arr[i++];
            sum3 += arr[j--];
        }
    }
    if (i == j)
    {
        if (sum1 < sum3)
            sum1 += arr[i];
        if (sum1 > sum3)
            sum3 += arr[j];
    }
    if (sum1 == sum3)
        ans = sum1;
    return ans;
}

/*  2nd Solution

long long threeWaySplit(int n, vector<int> arr){

    long long int ans=0,si=0,sj=0;
    int i=0,j=n-1;
    si=si+arr[i];
    sj=sj+arr[j];
    while(i<j)
    {
        if(si==sj)
        {
            ans=si;
            i++;
            j--;
            si+=arr[i];
            sj+=arr[j];
        }
        if(si>sj)
        {
            j--;
            sj=sj+arr[j];
        }
        if(si<sj)
        {
            i++;
            si=si+arr[i];
        }
    }
    return ans;
}

*/