EN ESTE NO FUNCIONA LA RECURSION
SI LA COMPLEJIDAD ES MUY AJUSTADA NO HACER RECURSION

void solve()
{
  int n, m; cin >> n >> m;
  vector<string> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  vector<vector<int>>dp(n, vector<int>(m, 0));
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (v[i][j] == '#') {
	dp[i][j] = 0;
	continue;
      }
      if (i-1 >= 0)  
	dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;

      if (j-1 >= 0)  
	dp[i][j] = (dp[i][j] + dp[i][j-1]) % mod;
    }
  }
  cout << dp[n-1][m-1] << '\n';
}

