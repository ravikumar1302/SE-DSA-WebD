/*
Convert Number To Words CodeStudio

Problem statement
You are given an Integer ‘N’ you have to convert the integer to words.

For example you are given integer N = 2234 then you have to return the string “two thousand two hundred and thirty four”.

Detailed explanation ( Input/output format, Notes, Images )
    Constraints :
    1 <= T <= 100
    1 <= N <= 999999999
    Time Limit: 1 sec

    Sample Input 1 :
    3
    1234
    45821
    555093
    Sample Output 1 :
    one thousand two hundred and thirty four
    forty five thousand eight hundred and twenty one
    five lakh fifty five thousand and ninety three
    Explanation of Sample Input 1 :
    For the first test case:
    The given integer is 1234 we can see that in words it is represented as “one thousand two hundred and thirty four”.

    For the second test case:
    The given integer is 45821; we can see that in words it is represented as “forty five thousand eight hundred and twenty-one”.

    For the third test case
    The given integer is 555093; we can see that in words it is represented as “five lakh fifty five thousand and ninety three”.

    Sample Input 2 :
    3
    99999
    1000
    30000
    Sample Output 2 :
    ninety nine thousand nine hundred and ninety nine
    one thousand
    thirty thousand
*/

#include <bits/stdc++.h>

vector<string> ones = {
    "zero", "one", "two", "three", "four", "five", "six", "seven",
    "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
    "eighteen", "nineteen"};

vector<string> tens = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

string handleAll(int n)
{
    if (n == 0)
        return "";
    else if (n < 20)
        return ones[n];
    else if (n < 100)
        return tens[n / 10] + (n % 10 ? " " + ones[n % 10] : "");

    else if (n < 1000)
    {
        return ones[n / 100] + " hundred" + (n % 100 ? " and " + handleAll(n % 100) : "");
    }

    else if (n < 100000)
    {
        int rem = n % 1000;
        return handleAll(n / 1000) + " thousand" +
               (rem ? (rem < 100 ? " and " : " ") + handleAll(n % 1000) : "");
    }

    else if (n < 10000000)
    {
        int rem = n % 100000;
        return handleAll(n / 100000) + " lakh" +
               (rem ? (rem < 100 ? " and " : " ") + handleAll(n % 100000) : "");
    }

    else
    {
        int rem = n % 10000000;
        return handleAll(n / 10000000) + " crore" +
               (rem ? (rem < 100 ? " and " : " ") + handleAll(n % 10000000) : "");
    }
}