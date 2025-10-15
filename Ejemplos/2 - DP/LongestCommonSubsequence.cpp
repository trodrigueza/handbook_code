string s, t;

int dp[3005][3005];

int go(int i, int j)
{
  if (i >= s.size() or j >= t.size()) return 0;
  if (dp[i][j] != -1) return dp[i][j];
  if (s[i] == t[j]) return dp[i][j] = 1 + go(i+1, j+1);

  return dp[i][j] = max( go( i+1, j ), go( i, j+1 ));
}

string ans(int i, int j) 
{
  string ans;
  while (i < s.size() && j < t.size()) {
    if (s[i] == t[j]) {
      ans.push_back(s[i]);
      i++, j++;
    } else {
      if (go(i+1, j) >= go(i, j+1)) i++;
      else j++;
    }
  }
  return ans;
}

void solve() 
{
  cin >> s >> t;
  memset(dp, -1, sizeof dp);
  dp[s.size()-1][t.size()-1] = (s[s.size()-1] == t[t.size()-1] ? 1: 0);
  go(0, 0);
  string str = ans(0, 0);
  cout << str << '\n';
}
