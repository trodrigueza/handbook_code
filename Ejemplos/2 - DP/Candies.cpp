int dp[N][M];
vector<int> v;
int n;

int go(int i, int w) 
{
  if (w == 0) return 1;
  if (i >= n) return 0;
  if (dp[i][w] != -1) return dp[i][w];

  int ans = 0;
  for (int j = 0; j <= v[i]; j++) {
    if (w - j < 0) break;
    ans = (ans + go(i+1, w - j)) % mod;
  }

  return dp[i][w] = ans;
}

void solve()
{
  int k; cin >> n >> k;
  memset(dp, -1, sizeof dp);
  v.resize(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  vector<int> pre(k+1, 1);
  for (int i = n-1; i >= 0; i--) {
    for (int j = 0; j <= k; j++) {
      if (j-v[i]-1 < 0) dp[i][j] = pre[j];
      else dp[i][j] = (pre[j] - pre[j-v[i]-1]) % mod;
    }
    for (int j = 0; j <= k; j++) {
      if (j == 0) pre[j] = dp[i][j];
      else pre[j] = (dp[i][j] + pre[j-1]) % mod;
    }
  }

  cout << (dp[0][k] + mod) % mod << '\n';
  //cout << go (0, k) << '\n';
}
