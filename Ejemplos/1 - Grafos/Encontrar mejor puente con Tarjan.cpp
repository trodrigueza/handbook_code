#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 100005;
vector<int> g[MAXN];
int n, m;
vector<pair<int,int>> bridges;

int timer = 0;
int tin[MAXN], low[MAXN], sub[MAXN];
bool visited[MAXN];
int best = 0;

int comb2(int x) { return x * (x - 1) / 2; }

int dfs(int v, int p = -1) 
{
  visited[v] = true;
  tin[v] = low[v] = timer++;
  sub[v] = 1;

  for (int to : g[v]) {
    if (to == p) continue;

    if (visited[to]) {
      low[v] = min(low[v], tin[to]);
    } else {
      sub[v] += dfs(to, v);
      low[v] = min(low[v], low[to]);

      if (low[to] > tin[v]) {
        int s = sub[to];
        int total = comb2(s) + comb2(n - s);
        best = min(best, total);
      }
    }
  }

  return sub[v];
}

void solve() 
{
  cin >> n >> m;
  for (int i = 0; i < n; i++) g[i].clear();

  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  timer = 0;
  fill(visited, visited + n, false);

  best = comb2(n);
  dfs(0, -1);

  cout << best << '\n';
}

int32_t main() 
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t = 1;
  cin >> t;
  while (t--) solve();
}
