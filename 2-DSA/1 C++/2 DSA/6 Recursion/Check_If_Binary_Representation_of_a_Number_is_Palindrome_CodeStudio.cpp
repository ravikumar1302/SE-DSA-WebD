
// Check_If_Binary_Representation_of_a_Number_is_Palindrome_CodeStudio

bool checkPalindrome(long long N)
{
	string s = "";
    
    while(N)
    {
        int rem = N%2;
        s.push_back(rem);
        N = N/2;
    }
    
    int i = 0, j = s.length()-1;
    while(i < j)
    {
        if(s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
    
}