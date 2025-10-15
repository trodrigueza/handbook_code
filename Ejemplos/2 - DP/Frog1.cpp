void solve()
{
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  vector<int> dp(n+1, INF);
  dp[0] = 0;

  for (int i = 1; i <= n; i++) {
    if (i - 2 < 0 or i - 3 < 0) {
      dp[i] = dp[i-1] + abs(v[0]-v[i-1]);
      continue;
    }
    dp[i] = min(dp[i-1] + abs(v[i-2]-v[i-1]), dp[i-2] + abs(v[i-3]-v[i-1]));
  }
  cout << dp[n] << '\n';
}
