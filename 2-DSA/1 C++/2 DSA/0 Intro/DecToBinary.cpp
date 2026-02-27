#include <iostream>
#include<math.h>
using namespace std;
int main() 
{
	int n;
	cout<<"Enter n : ";
	cin>>n;
	int ans=0; 
 	int i=0;
	while(n!=0)
	{
		int bit=n&1;
		ans=(bit*pow(10,i) + ans);
    	n=n>>1; //right shift
    	i++;
	}
	cout<<"Binary of n is: "<<ans;
	return 0;
}

// Approach-2
// Without using right shift

#include<iostream>
using namespace std;
int main()
{
    int decimalNum, binaryNum=0, mul=1, rem;
    cout<<"Enter the Decimal Number: ";
    cin>>decimalNum;
    while(decimalNum>0)
    {
        rem = decimalNum%2;
        binaryNum = binaryNum+(rem*mul);
        mul = mul*10;
        decimalNum = decimalNum/2;
    }
    cout<<"\nEquivalent Binary Value: "<<binaryNum;
    cout<<endl;
    return 0;
}