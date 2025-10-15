#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ff first
#define ss second
#define pii pair<int, int>
#define pll pair<ll, ll>
#define int long long

ll mod = ((1e9)+7);
const int INF = 1e9;

int n;  // Nodos del árbol
vector<int> graph[200005]; // Árbol con lista de adyacencias.
int timer = 0, tin[200005], euler_tour[400005]; // Timer, tiempo de entrada y el Euler tour
vector<bool> vis(200005, false);

void dfs(int node = 1, int parent = -1) {
  vis[node] = true;
  tin[node] = timer;
  euler_tour[timer++] = node;
  for (int i : graph[node]) {
    if (!vis[i]) {
      dfs(i, node);
      euler_tour[timer++] = node;
    }
  }
}

void solve()
{
  int m, k; cin >> n >> m >> k;

  vector<int> loop(n+1,0);

  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
    if (a==b) loop[a] = 1;
  }
  if (m==0) {
    cout << 1 << " " << 1 << '\n';
    return;
  }

  dfs();

  int blk = ceil((2.0 * n) / k);
  int idx = 0;
  for (int i = 0; i < k; i++) {
    cout << blk << ' ';
    int dis = timer - idx;
    int j = 0;
    for (; j < blk && idx < timer; j++, idx++) {
      cout << euler_tour[idx] << ' ';
    }
    if (dis < blk) {
      bool f = 1;
      if (loop[euler_tour[timer - 1]]) {
	for (; j < blk; j++) cout << euler_tour[timer - 1] << ' ';
      } else {
	for (; j < blk; j++) {
	  cout << euler_tour[timer - 1 - f] << ' ';
	  f = !f;
	}
      }
    }
    cout << '\n';
  }
}

int32_t main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  //cin >> t;
  while (t--) solve();
}
