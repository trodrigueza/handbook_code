void solve()
{
  int n, w; cin >> n >> w;
  vector<vector<int>> g(n);
  for (int i = 0; i < w; i++) {
    int from, to; cin >> from >> to;
    from--, to--;
    g[from].push_back(to);
  }
  vector<int> dp(n, -1);

  function<int(int)> dfs = [&] (int v) {
    if (dp[v] != -1) return dp[v];

    dp[v] = 0;
    for (auto child : g[v]) {
      dp[v] = max(dp[v], 1 + dfs(child));
    }

    return dp[v];
  };

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, dfs(i));
  }
  cout << ans << '\n';
}
