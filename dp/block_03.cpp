/*
Each project can be launched in one of the several possible ways, or not launched at all.
The team of analysts has provided the expected costs and revenue for each possible launch way of each project.
The system is set up so that the costs are spent from a fixed budget that has been approved by the management in advance. At the same time, any revenue received does not increase the budget for starting other projects that have not yet been launched.
The management is only interested in the maximum total revenue. In other words, they are not interested in the total costs, except that they fit within the specified budget.
As a highly qualified specialist, you are asked to find the maximum total revenue*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int INF = 1e9;
const ll LLINF = 4e18;

ll mx = 0, b;
int n;
vector<vector<pii>> a;

void f(int id, ll bb, ll r) {
  mx = max(mx, r);
  if (id >= n) return;
  for (int k = 0; k < (int)a[id].size(); k++) {
    if (bb - a[id][k].second < 0) continue;
    f(id+1, bb - a[id][k].second, r + a[id][k].first);
  }
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> b;
  a.resize(n);
  for (int i = 0; i < n; i++) {
    int m; cin >> m;
    for (int j = 0; j < m; j++) {
      ll f, s; cin >> f >> s;
      a[i].push_back({f,s});
    }
    a[i].push_back({0,0});
  }
  f(0, b, 0ll);
  cout << mx << "\n";
}


