const int N = 21;
int dp[(1<<N)];
vector<vector<int>> v;
int n;
const int mod = 1e9 +7;

int go (int i,  int mask) 
{
  if(mask == 0) return 1;
  if (i>=n) return 0;
  if (dp[mask] != -1) return dp[mask];
  int ans = 0;
  for (int j = 0; j < n; j++) {
    // Si es mujer sin emparejar entonces ver si se puede emparejar.
    if (mask & (1 << j)) {
      if (v[i][j] == 1) 
	ans = (ans + go ( i + 1, mask ^ (1 << j))) % mod;
    }
  }

  return dp[mask] = ans;
}

void solve() 
{
  cin >> n;
  v.resize(n);
  memset(dp, -1, sizeof dp);
  for (int i =0 ; i < n; i++) v[i].resize(n);
  for (int i = 0; i < n; i++) {
    for (int j =0 ; j < n; j++) cin >> v[i][j];
  }
  cout << go (0, (1 << n)-1) << '\n';
}
