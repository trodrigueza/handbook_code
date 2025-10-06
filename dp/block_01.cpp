// easy version
const int N = 1000;
using BS = bitset<N+1>;
void solve() {
  int n, p; cin >> n >> p;
  vector<int> a(p);
  for (int i = 0; i < p; i++) cin >> a[i];
  BS dp;
  dp.set(0);
  for (auto x : a) {
      dp |= (dp << x);
  }
  cout << (dp.test(n) ? "YES\n" : "NO\n");
}

// For all subsets that sum k, what are the possible sums of those subsets
const int N = 500;
using BS = bitset<N+1>;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  
  vector<BS> dp(k+1);
  dp[0].set(0);
  for (auto x : a) {
    for (int i = k; i >= x; i--) {
      if (dp[i-x] == 0) continue;
      dp[i] |= dp[i-x];
      dp[i] |= (dp[i-x] << x);
    }
  }
  
  cout << dp[k].count() << "\n";
  for (int i = 0; i <= k; i++)
    if (dp[k].test(i)) cout << i << " ";
  cout << "\n";
}
