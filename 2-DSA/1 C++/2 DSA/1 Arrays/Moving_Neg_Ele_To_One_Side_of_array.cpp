// Moving_Neg_Ele_To_One_Side_of_array

class Solution{
    public:
    void segregateElements(int arr[],int n)
    {
        // Your code goes here
        int pos=0,a2[n];
        for(int i=0;i<n;i++)
        {
            if(arr[i]>0)
            {    //pos++;
                a2[pos++]=arr[i];
            }
        }
        //pos=pos--;
        for(int i=0;i<n;i++)
        {
            if(arr[i]<0)
            a2[pos++]=arr[i];
        }
        for(int i=0;i<n;i++)
        {
            arr[i]=a2[i];
        }
    }
};