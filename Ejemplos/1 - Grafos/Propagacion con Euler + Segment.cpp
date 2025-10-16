#define int long long
const int MAXN = 200005;

int n, m;
vector<int> graph[MAXN];
int a[MAXN];
int tin[MAXN], tout[MAXN], euler_tour[MAXN], depth[MAXN];
int timer = 0;

int seg[4*MAXN], lazy[4*MAXN];

void dfs(int node = 1, int parent = -1, int d = 0) 
{
  depth[node] = d;
  tin[node] = timer;
  euler_tour[timer++] = node;
  for (int v : graph[node]) {
    if (v == parent) continue;
    dfs(v, node, d + 1);
  }
  tout[node] = timer - 1;
}

void push(int idx, int l, int r) 
{
  if (lazy[idx] != 0) {
    seg[idx] += lazy[idx];
    if (l != r) {
      lazy[idx*2] += lazy[idx];
      lazy[idx*2+1] += lazy[idx];
    }
    lazy[idx] = 0;
  }
}

void update(int idx, int l, int r, int ql, int qr, int val) 
{
  push(idx, l, r);
  if (r < ql || l > qr) return;
  if (ql <= l && r <= qr) {
    lazy[idx] += val;
    push(idx, l, r);
    return;
  }
  int mid = (l + r) / 2;
  update(idx*2, l, mid, ql, qr, val);
  update(idx*2+1, mid+1, r, ql, qr, val);
}

int query(int idx, int l, int r, int pos) 
{
  push(idx, l, r);
  if (l == r) return seg[idx];
  int mid = (l + r) / 2;
  if (pos <= mid) return query(idx*2, l, mid, pos);
  else return query(idx*2+1, mid+1, r, pos);
}
void solve() 
{
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs();

  while (m--) {
    int t; cin >> t;
    if (t == 1) {
      int x; int val;
      cin >> x >> val;
      if (depth[x] % 2 == 0) update(1, 0, n - 1, tin[x], tout[x], val);
      else update(1, 0, n - 1, tin[x], tout[x], -val);
    } else {
      int x; cin >> x;
      int add = query(1, 0, n - 1, tin[x]);
      if (depth[x] % 2 == 0) cout << a[x] + add << '\n';
      else cout << a[x] - add << '\n';
    }
  }
}
