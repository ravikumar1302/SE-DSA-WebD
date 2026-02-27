/*
Modular_Exponentiation_Codestudio

You are given a three integers 'X', 'N', and 'M'. Your task is to find ('X' ^ 'N') % 'M'. 
A ^ B is defined as A raised to power B and A % C is the remainder when A is divided by C.
*/

#include <bits/stdc++.h> 
int modularExponentiation(int x, int n, int m) {
	int res=1;
    while(n>0)
    {
        if(n&1)    //odd
        {
            res= (1ll*res*(x)%m)%m;
        }
        x=(1ll * (x)%m * (x)%m)%m;
        n=n>>1;
    }
    return res;
}