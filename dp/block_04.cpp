/*
Peter and Vasya are playing a game. They have three piles of stones with sizes n1, n2, n3 respectively. On each turn, it is allowed to take exactly a1, a2, ..., ak-1, ak stones from any one pile. Peter and Vasya take turns to take stones, with Peter starting first. The player who cannot make a move loses. Determine the name of the winner.
*/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
const int INF = 1e9;
const ll LLINF = 4e18;
const int N = 102;
 
int dp[N][N][N];
 
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n1, n2, n3, K; cin >> n1 >> n2 >> n3 >> K;
  vector<int> kk(K);
  for (int i = 0; i < K; i++) {
    cin >> kk[i];
  }
  
  dp[0][0][0] = 0;

  for (int i = 0; i <= n1; i++) {
    for (int j = 0; j <= n2; j++) {
      for (int k = 0; k <= n3; k++) {
        if (i == 0 && j == 0 && k == 0) continue;
        bool f = 0;
        for (int l = 0; l < K; l++) {
          if (i >= kk[l] && !dp[i-kk[l]][j][k]) f = 1;
          if (j >= kk[l] && !dp[i][j-kk[l]][k]) f = 1;
          if (k >= kk[l] && !dp[i][j][k-kk[l]]) f = 1;
        }
        dp[i][j][k] = f;
      }
    }
  }
 
  cout << ((dp[n1][n2][n3]) ? "Peter" : "Vasya") << "\n";
}

