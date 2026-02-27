/*
Minimum_Difference


*/

class Solution {
  public:
  
  int checkdiff(int a[26], int b[26])
    {
        int cnt = 0;
        for(int i=0;i<26;i++)
        {
            if(a[i]==b[i] && a[i] != 0 && b[i] != 0)
                cnt++; 
        }
        return cnt;
    }
  
int minimumDifference(string s, vector<string> list) {
        
    int cnt = 0;
    
    int count1[26]={0}; // For main string
    for(int i=0;i<s.length();i++) 
        {
            int index=s[i]-'a';
            count1[index]++;
        }
    
    for(auto m : list)
        {
            int count2[26]={0};     // For list
            
            for(int i=0; i<m.length(); i++)  
            {
                int index=m[i]-'a';
                count2[index]++;
            }
            
            int cntNew = ( m.size() - checkdiff(count1, count2) );
            cnt = min(cntNew, cnt);
        }
        
        return cnt; 
    }
};