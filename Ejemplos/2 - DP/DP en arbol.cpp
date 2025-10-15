void solve()
{
  int n; cin >> n;
  vector<vector<int>> tree(n);
  vector<pii> ranges(n);

  for (int i = 0; i < n-1; i++) {
    int tmp; cin >> tmp; tmp--;
    tree[tmp].push_back(i+1);
  }

  for (int i = 0; i < n; i++) {
    cin >> ranges[i].ff;
    cin >> ranges[i].ss;
  }

  int ans = 0;

  function<int(int)> dfs = [&](int v) {
    int sum = 0;
    for (auto a: tree[v]) sum += dfs(a);

    if (sum < ranges[v].ff) {
      sum = ranges[v].ss;
      ans++;
    }
    return min(sum, ranges[v].ss);
  };

  dfs(0);

  cout << ans << '\n';
}
