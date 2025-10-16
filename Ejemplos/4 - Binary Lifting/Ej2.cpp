vector<vector<int>> dp(40, vector<int>(2e5+5));
vector<int> v(2e5+5);

void solve() 
{
  int n , k; cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> v[i];

  // Por la input
  for (int i = 0; i < n; i++) dp[0][i] = v[i];

  // 61 pa los ancestros
  for (int i = 1; i < 40; i++) {
    for (int j = 0; j < n; j++) {
      // El estado actual se consigue con el ancestro anterior y además como piden la suma 
      // se tiene que sumar con la manera en la que se llegó aquí que es dp[i-1][j] + j
      dp[i][j] = dp[i-1][j] + dp[i-1][ (j+dp[i-1][j])%n ];
    }
  }

  int ans = 0;
  for (int i = 0; i < 40; i++) {
    if (k & 1) {
      int res = dp[i][ans%n];
      ans += res;
    }
    k >>= 1;
  }
  cout << ans << '\n';
}

