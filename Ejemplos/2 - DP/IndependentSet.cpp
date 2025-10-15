const int N = 1e5+5;

int dp[N][2];
int n;
vector<vector<int>> tree;

int go(int i, bool color, int parent)
{
  if (dp[i][color] != -1) return dp[i][color];
  int ans = 1;
  for (auto child : tree[i]) {
    // Color = 1 = white;
    // Color = 0 = black;
    if (child == parent) continue;
    int actual = 0;
    if (color) {
      actual = (actual + go (child, !color, i)) % mod;
      actual = (actual + go (child, color, i)) % mod;
    } else {
      actual = (actual + go (child, !color, i)) % mod;
    }
    ans = (ans * (actual == 0 ? 1: actual)) % mod;
  }
  return dp[i][color] = ans;
}

void solve()
{
  cin >> n;
  tree.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      dp[i][j] = -1;
    }
  }
  for (int i= 0; i < n-1; i++) {
    int from, to; cin >> from >> to;
    to--, from--;
    tree[from].push_back(to);
    tree[to].push_back(from);
  }
  int ans = go (0, 1, -1);
  ans = (ans + go (0, 0, -1)) % mod;
  cout << ans << '\n';
}

