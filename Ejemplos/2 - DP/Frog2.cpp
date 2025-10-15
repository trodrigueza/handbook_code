void solve()
{
  int n, k; cin >> n >> k;
  vector<int> h(n+1), dp(n+1, INF);
  for (int i = 1; i <= n; i++) cin >> h[i];

  dp[0]  = 0;
  h[0] = h[1];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k and i-j >= 0; j++) {
      dp[i] = min(dp[i], dp[i-j] + abs(h[i] - h[i-j]));
    }
  }
  cout << dp[n] << '\n';
}

