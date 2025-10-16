vector<int> a(2e5+5);
vector<vector<int>> dp(61, vector<int>(2e5+5));

void solve() 
{
  int n, k; cin >> n >> k;
  for (int i =0 ; i < n; i++)  cin >> a[i];

  for (int j = 0; j < n; j++) dp[0][j] = a[j]-1;
  for (int i = 1; i < 61; i++) {
    for (int j = 0; j < n; j++) {
      dp[i][j] = dp[i-1][ dp[i-1][j] ];
    }
  }

  int ans = 0;
  for (int i = 0; i < 61; i++) {
    if (k & 1) {
      ans = dp[i][ans];
    }
    k >>= 1;
  }
  cout << ans+1 << '\n';
}
