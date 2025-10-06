/*
You are given a directed graph that is a rooted tree. The edges of the graph are directed from children to parents, and from each vertex, it is possible to reach the root through the edges. Each vertex of the graph contains an integer. It is guaranteed that all these integers are distinct. Consider all paths from the leaves to the root; here, a leaf is a vertex without children. For each path, calculate the sum of the k largest numbers occurring in its vertices, or all of them if there are fewer than k numbers on the path. Find the maximum such sum.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

vector<pair<ll, pii>> dp; // i = {sum, {puse/quité}}
vector<vector<int>> gd, g;
vector<ll> w;

void bfs(set<ll> &s, int i, int j) {
  queue<int> q;
  q.push(i);
  while (q.size()) {
    int cur = q.front(); q.pop();
    if (cur == j) return;
    if (dp[cur].second.first != -1) s.erase(dp[cur].second.first);
    if (dp[cur].second.second != -1) s.insert(dp[cur].second.second);

    q.push(gd[cur][0]);
  }
}
int f = 0, k;
void dfs (set<ll> &K, int i){
  // cout << "| " << w[i] << " " <<  dp[i].first <<"\n";
  if ((int)g[i].size() == 0) {
    f = i;
    return;
  }
  
  for (auto v : g[i]) {
    if (f) {
      bfs(K, f, i);
      f = 0;
    }

    int size = K.size();
    ll tmp = *(K.begin());
    ll sum = dp[i].first;
    if (size == k && w[v] > tmp) {
      K.erase(tmp);
      K.insert(w[v]);
      dp[v] = {sum - tmp + w[v], {w[v], tmp}};
    } else if (size < k) {
      K.insert(w[v]);
      dp[v] = {sum + w[v], {w[v], -1}};
    } else {
      dp[v] = {sum, {-1, -1}};
    }
    dfs(K, v);
  }
};


int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << *ss.begin() << "\n";
  int n; cin >> n >> k;
  g.resize(n+1);
  dp.resize(n+1);
  w.resize(n+1, 0);
  gd.resize(n+1);
  for (int i = 1; i <= n; i++) {
    int p; ll q; cin >> p >> q;
    w[i] = q;
    g[p].push_back(i);
    gd[i].push_back(p);
  }
  
  set<ll> K;
  dp[0] = {0ll, {-1ll, -1ll}};
  
  dfs(K, 0);

  ll ans = 0;
  for (auto &l : dp) ans = max(ans, l.first);
  cout << ans << "\n";
}
