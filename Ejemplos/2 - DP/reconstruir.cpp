const int N = 1e3+5;
const int M = 1e3+5;

array<int, 3> dp[N][M];
int n, m;
vector<int> a, b;

array<int, 3> go (int i, int j)
{
  if (i == a.size()) return {n-1, j, 0};
  if (j == b.size()) return {i, m-1, 0};
  if (dp[i][j][2] != -1) return dp[i][j];

  array<int, 3> ans = {i, j, 0};

  if (a[i] == b[j]) {
    array<int, 3> res = go ( i+1 , j+1 );
    return dp[i][j] = {i+1, j+1, 1 + res[2]};
  }

  array<int, 3> res = go ( i+1 , j );
  ans = {i+1, j, res[2]};

  res = go ( i , j+1 );
  if (res[2] > ans[2]) {
    ans = {i, j+1, res[2]};
  }

  return dp[i][j] = ans;
}

void solve()
{
  cin >> n >> m;
  a.resize(n);
  b.resize(m);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) 
      dp[i][j] = {-1,-1,-1};
  }

  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];
  auto res = go ( 0 , 0 );

  int i = 0, j = 0;
  cout << dp[i][j][2] << '\n';

  while (1) {
    if (a[i] == b[j]) cout << a[i] << ' ';
    int pv = i;
    i = dp[i][j][0];
    j = dp[pv][j][1];
    if (i == -1 or j == -1) break;
    if (i >= n or j >= m) break;
  }
  cout << '\n';
}

