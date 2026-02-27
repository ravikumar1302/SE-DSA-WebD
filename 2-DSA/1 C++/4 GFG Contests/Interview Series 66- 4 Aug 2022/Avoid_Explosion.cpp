/*
Avoid Exploasion

*/

class Solution {
  public:
    vector<string> avoidExplosion(vector<vector<int>> mix, int n, vector<vector<int>> danger, int m) 
      {
          vector<string> answer;
          
        //   sort(mix.begin(), mix.end());
        //   sort(danger.begin(), danger.end());
          
          for(int i=0; i<n; i++)
          {
              int x = mix[i][0];
              int y = mix[i][1];
              
              for(int j=0; j<m; j++)
              {
                  int p = danger[j][0];
                  int q = danger[j][1];
                  
                  if( (x == p && y == q) || (x == q && y == p) )
                  {
                    answer.push_back("No");
                    break;
                  }
              }
              
              if(answer.size() < i+1)
                answer.push_back("Yes");
          }
          
          return answer;
      }
};