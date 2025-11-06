const int oo = 1e9;
const int N = 2e5 + 5;

vector<vector<int>> tree;
int dp[N][32];
int depth[N];
int LOGv;

void dfs(int u = 1, int p = -1)
{
  dp[u][0] = p;
  for (int i = 1; i < LOGv; i++) {
    int mid = dp[u][i-1];
    dp[u][i] = (mid == -1) ? -1 : dp[mid][i-1];
  }
  for (int v : tree[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
}

int kth(int v, int k) 
{
  if (k > depth[v]) return -1;
  for (int i = 0; i < LOGv && v != -1; i++) {
    if (k & (1LL << i)) v = dp[v][i];
  }
  return v;
}

void solve() 
{
  int n, q; cin >> n >> q;

  tree.resize(n+1);
  LOGv = 1;
  while ((1LL << LOGv) <= n) LOGv++;
  memset(dp, -1, sizeof dp);
  memset(depth, 0, sizeof depth);


  for (int i = 2; i <= n; i++) {
    int a; cin >> a;
    tree[a].push_back(i);
    tree[i].push_back(a);
  }

  depth[1] = 0;
  dfs ();
}

