/*
Multiply_Strings_Leetcode_43
Multiply two strings GFG

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.
Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
 
    Example 1:
    Input: num1 = "2", num2 = "3"
    Output: "6"

    Example 2:
    Input: num1 = "123", num2 = "456"
    Output: "56088"
 

Constraints: Both num1 and num2 do not contain any leading zero, except the number 0 itself.
*/


// Youtube Link Solution : just go through the multiplication and array portion to understand, how carry and array is working : https://www.youtube.com/watch?v=1vZswirL8Y8

// Approach : the maximum no of digits in ans will be sum of digits in number to be multiplied. So, we will create an vector of that size and will enter the value in that vector  
// Time : O(N^2), as two loops are there


class Solution {
public:
    string multiply(string num1, string num2) {
        
        // Edge case
        if(num1 == "0" || num2 == "0")
            return "0";
        
        // Declaring an vector of size of total no of digits in (num1 + num2) and intitializing it with 0
        vector<int> ans_vector (num1.size() + num2.size(), 0);
        
        // build the ans by multiplying one digit at the time
        for(int i=num1.size()-1; i>=0; i--)
        {
            for(int j=num2.size()-1; j>=0; j--)
            {
                ans_vector[i+j+1] += (num1[i] - '0')*(num2[j] - '0');      // += to add the carry 
                ans_vector[i+j] += ans_vector[i+j+1]/10;         // Putting the carry at it's position, which will be added by above line in next iteration
                ans_vector[i+j+1] %= 10; 
            }
        }
        
        // There might be some leading 0's in vector, which are not needed
        int i=0;
        while(i < ans_vector.size() && ans_vector[i] == 0)
            i++;
        
        // Converting the vector to string
        string ans = "";
        while(i < ans_vector.size())
        {
            ans.push_back(ans_vector[i] + '0');
            i++;
        }
            
        return ans;
        
    }
};



// GFG : Note: The numbers can be negative
// To deal with negative numbers, the approach is little different, we have to check which no is negative

class Solution{
  public:
    /*You are required to complete below function */
    string multiplyStrings(string s1, string s2) {
       
               // Edge case
        if(s1 == "0" || s2 == "0")
            return "0";
        
        // To check the negative digits
        bool neg1 = false;
        bool neg2 = false;
        if(s1[0] == '-')
            {
                neg1 = true;
                s1[0] = '0';
            }
        if(s2[0] == '-')
            {
                neg2 = true;
                s2[0] = '0';
            }
        
        
        // Declaring an vector of size of total no of digits in (s1 + s2) and intitializing it with 0
        vector<int> ans_vector (s1.size() + s2.size(), 0);
        
        // build the ans by multiplying one digit at the time
        for(int i=s1.size()-1; i>=0; i--)
        {
            for(int j=s2.size()-1; j>=0; j--)
            {
                ans_vector[i+j+1] += (s1[i] - '0')*(s2[j] - '0');      // += to add the carry 
                ans_vector[i+j] += ans_vector[i+j+1]/10;         // Putting the carry at it's position, which will be added by above line in next iteration
                ans_vector[i+j+1] %= 10; 
            }
        }
        
        // There might be some leading 0's in vector, which are not needed
        int i=0;
        while(i < ans_vector.size() && ans_vector[i] == 0)
            i++;
        
        // Converting the vector to string
        string ans = "";
        if( (neg1 == true && neg2 == false) || (neg1 == false && neg2 == true) )  // If one is positive and one is negative
            ans.push_back('-');
        
        while(i < ans_vector.size())
        {
            ans.push_back(ans_vector[i] + '0');
            i++;
        }
        
        return ans;
    }
};