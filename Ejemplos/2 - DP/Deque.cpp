int dp[N][N];
vector<int> vals;

int go(int i, int j)
{
  if (j < i) return 0;
  if (i == j) return vals[i];
  if (dp[i][j] != -1) return dp[i][j];
  return dp[i][j] = max(vals[i] - go (i+1, j), vals[j] - go (i, j-1));
}

void solve()
{
  int n; cin >> n;
  vals.resize(n);
  memset(dp, -1, sizeof dp);
  for (int i = 0; i < n; i++) cin >> vals[i];
  cout << go(0, n-1) << '\n';
}
