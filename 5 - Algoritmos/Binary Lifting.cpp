Binary Lifting, la idea es como lograr hacer aplicaciones de funciones, como encontrar el k-esimo ancestro de un nodo con una complejidad de O(log n).

vector<int> apps;
vector<int> a;

int apply (int j) {
  return apps[j]-1;
}

void solve() {
  vector<vector<int>> dp(61, vector<int>(2e5));
  int n, k; cin >> n >> k;
  a.resize(n);
  apps.resize(n);

  for (int i = 0; i < n; i++) cin >> apps[i];
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) dp[0][i] = apply(i);

  for (int p = 1; p < 61; p++) {
    for (int i = 0; i < n; i++) {
      dp[p][i] = dp[p-1][ dp[p-1][i] ];
    }
  }

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    int pos = i;
    for (int p = 0; p < 61; p++)
      if ((k >> p) & 1)
	pos = dp[p][pos];
    ans[i] = a[pos];
  }
  for (auto a : ans) cout << a << ' ';
  cout << '\n';
}
