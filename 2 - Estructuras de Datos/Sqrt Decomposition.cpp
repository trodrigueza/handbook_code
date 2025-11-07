Código de solución de Holes usando sqrt decomposition, algo importante es que el tamaño de los bloques no siempre es \sqrt n, hay casos en los que se puede mejorar usando otro tamaño de bloque.
const int N = 1e5 +5;

vector<int> a;
array<int, 2> dp[N];

int n;

struct bucket {
  int l, r, lazy;
  bucket(int l, int r) : l(l), r(r), lazy(0) {build();}
  void build() {
    for (int i = r; i >= l; i--) {
      int jump = i + a[i];
      if (jump > r and jump < n) {
	dp[i] = { 1 , jump };
      } else if (jump >= n) {
	dp[i] = { 1 , i };
      } else {
	dp[i] = { dp[jump][0] + 1, dp[jump][1] };
      }
    }
    lazy = 0;
  }

  void updateRange(int L, int R, ll v) {
    if(L == l && R == r) lazy += v;
    else { 
      for(int i = L; i <= R; i++) a[i] += v; 
      build();
    }
  }

  void updatePoint(int idx, int v) {
    a[idx] = v;
    build();
  }

  int query(int L, int R) {
    int ans = INT_MIN;
    return ans;
  }

  array<int, 2> queryPoint(int idx) {

    int daddy = dp[idx][1];
    int steps = dp[idx][0];

    return { daddy , steps };
  }
};

void solve()
{
  int q; cin >> n >> q;
  a.resize(n);

  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < N; i++) {
    dp[i] = {-1, -1};
  }

  int S = sqrt(n);
  vector<bucket> b;
  for (int i = 0; i < n; i += S) {
    b.push_back(bucket(i, min( i + S-1 , n-1 )));
  }

  for (int i = 0; i < q; i++) {
    int t; cin >> t;
    switch (t) {
      case 0: {
		int idx, x; cin >> idx >> x;
		idx--;
		int bid = idx / S;
		b[bid].updatePoint(idx, x);
		break;
	      }
      case 1: {
		int idx; cin >> idx;
		idx--;
		int bid = idx / S;
		array<int, 2> res = { 0 , 0 };
		int prv = -1;
		for (int i = bid; i < b.size(); i = idx / S) {
		  array<int, 2> cur =  b[i].queryPoint(idx);
		  if (i == prv) break;
		  if (cur[0] == res[0]) {
		    res[1]++;
		    break;
		  }
		  idx = cur[0];
		  res[1] += cur[1];
		  res[0] = idx;
		  prv = i;
		}
		cout << res[0] + 1 << " " << res[1] << '\n';
		break;
	      }
    }
  }
}

