/*
Count_Occurences_of_Anagrams_GFG

Given a word pat and a text txt. Return the count of the occurences of anagrams of the word in the text.

    Example 1:
    Input: txt = forxxorfxdofr, pat = for
    Output: 3
    Explanation: for, orf and ofr appears in the txt, hence answer is 3.

    Example 2:
    Input: txt = aabaabaa, pat = aaba
    Output: 4
    Explanation: aaba is present 4 times in txt.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(26) or O(256)
*/

// Note : I  tried to direct compare count_pat == window, that will give error, because I have taken array not vector, and it will just compare address of arr[0] which will result NULL

class Solution{
public:
bool checkequal(int a[26], int b[26])
    {
        for(int i=0;i<26;i++)
        {
            if(a[i]!=b[i])
                return 0; 
        }
        return 1;
    }
    
	int search(string pat, string txt) {
	    
	    int k = pat.length();
	    int count_pat[26] = {0};
	    int i=0;
	    for(; i<k; i++)
	    {
	        int index = pat[i] - 'a';
	        count_pat[index]++;
	    }
	   
	   int window[26] = {0};
	   int ans = 0;
	   i=0;
	   // First window 
	   for(; i<k && i< txt.length(); i++)
	   {
	       int index = txt[i] - 'a';
	       window[index]++;
	   }
	   if(checkequal(window, count_pat) )
	        ans++;
	    
	    // Remanining windows
	    for(; i<txt.length(); i++)
	    {
	        int next_index = txt[i] - 'a';
	        window[next_index]++;
	        
	        int index_to_del = txt[i - k] - 'a';
	        window[index_to_del]--;
	        
	        if(checkequal(window, count_pat) )
	            ans++;
	    }
	    return ans;
	}

};