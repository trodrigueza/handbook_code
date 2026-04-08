const int oo = 1e9;

const int N = 100005;
vector<int> tree[N];


int sz[N]; 
bool removed[N];
int parent[N]; 
vector<int> ancestors[N];
vector<int> dists[N];
multiset<int> distances_to_red[N];

int dfs(int u, int p) 
{
  sz[u] = 1;
  for (int v : tree[u]) {
    if (v == p or removed[v]) continue;
    sz[u] += dfs( v, u );
  }
  return sz[u];
}

// Encuentra centroid de subarbol raiz en u tamaño n
int find_centroid(int u, int p, int n) {
  for (int v : tree[u]) {
    if (v != p && !removed[v] && sz[v] > n / 2) {
      return find_centroid( v, u, n );
    }
  }
  return u;
}

void dfs_dist(int u, int p, int dep, int centroid) 
{
  ancestors[u].push_back(centroid);
  dists[u].push_back(dep);
  for (int v : tree[u]) {
    if (v == p or removed[v]) continue;
    dfs_dist(v, u, dep + 1, centroid);
  }
}

void build(int u, int p) 
{
  int n = dfs( u, -1 ), c = find_centroid( u , -1 , n );
  removed[c] = 1;
  parent[c] = p;

  dfs_dist( c , -1 , 0 , c );

  for (int v : tree[c]) 
    if (!removed[v]) build( v , c );
}

void init(int n) 
{
  fill(removed, removed + n + 1, 0);
  for (int i = 1; i <= n; i++) {
    ancestors[i].clear();
    dists[i].clear();
    distances_to_red[i].clear();
    parent[i] = -1;
  }
}

void update(int u) 
{
  for (int i = 0; i < ancestors[u].size(); i++) {
    int c = ancestors[u][i];
    int d = dists[u][i];
    distances_to_red[c].insert(d);
  }
}

int query(int u) 
{
  int res = oo;
  for (int i = 0; i < ancestors[u].size(); i++) {
    int c = ancestors[u][i];
    int d = dists[u][i];
    if (!distances_to_red[c].empty()) {
      res = min(res, d + *distances_to_red[c].begin());
    }
  }
  return res;
}

void solve() 
{
  int n, q; cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  init( n );
  build( 1 , -1 );
  update( 1 );

  while (q--) {
    int type, u; cin >> type >> u;
    if (type == 1) update( u );
    else cout << query( u ) << '\n';
  }
}
