/*
Square_root_Codestudio
You are given a positive integer ‘N’. Your task is to find and return its square root. 
If ‘N’ is not a perfect square, then return the floor value of sqrt(N).
*/

int sqrtN(long long int N)
{
    // Write your code here.
    int s=0;
    int e=1e+16; //or unsigned int e = N;
    long long int mid=s+(e-s)/2;

    while(s<=e){
        if(N==1ll*mid*mid)
            return mid;
        else if(N<1ll*mid*mid){
            e=mid-1;
        }
        else{
            s=mid+1;
        }
        mid=s+(e-s)/2;
    }
    return e;
}

/*
class Solution {
public:
    int binarysearch(int n)
    {
        int s=0,e=n;
        long long int mid=s+(e-s)/2;
        long long int ans=-1;
        while(s<=e)
        {
            long long int square=mid*mid;
            if(square==n)
                return mid;
            if(square<n)
            {
                ans=mid;
                s=mid+1;
            }
            else
                e=mid-1;
            mid=s+(e-s)/2; 
        }
       return ans; 
    }
    int mySqrt(int x) {
        return binarysearch(x);
    }
};  
*/