/*
From the first cup he drinks during the session, Evgeny gets 1 units of relaxation, where 1 is the relaxation coefficient for the first cup of tea he drinks. From the next cup, he gets 2 units of relaxation, where 2 is the relaxation coefficient for the second cup of tea he drinks. And so on: from the i-th cup he drinks, Evgeny gets i*x_i units of relaxation.
Help Evgeny determine the maximum total amount of relaxation he can achieve during the Da Hong Pao session.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int INF = 1e9;
const ll LLINF = 4e18;
const int N = 5005;

ll dp[N][N];

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  memset(dp, 0, sizeof(dp));
  for (int l = n - 1; l >= 0; l--) {
    for (int r = l; r < n; r++) {
      
      int k = n - (r - l + 1) + 1;
      if (l == r) {
        dp[l][r] = k * a[l];
      } else {
        dp[l][r] = max(k * a[l] + dp[l + 1][r], k * a[r] + dp[l][r - 1]);
      }
    }
  }

  cout << dp[0][n-1] << "\n";
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  while (t--) {
    solve();
  }
}


