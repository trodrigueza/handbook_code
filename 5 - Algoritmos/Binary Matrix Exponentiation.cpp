using ll = long long;
const ll MOD = 1e9+7;

struct Mat {
  int n;
  vector<vector<ll>> a;

  Mat(int n = 0, bool ident = false) : n(n), a(n, vector<ll>(n, 0)) {
    if (ident)
      for (int i = 0; i < n; i++) a[i][i] = 1;
  }

  static Mat ident(int n) { return Mat(n, true); }

  Mat operator*(const Mat& o) const {
    Mat r(n);
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < n; k++) if (a[i][k]) {
        __int128 aik = a[i][k];
        for (int j = 0; j < n; j++) if (o.a[k][j]) {
          r.a[i][j] = (r.a[i][j] + (aik * o.a[k][j]) % MOD) % MOD;
        }
      }
    }
    return r;
  }
};

Mat mpow(Mat A, unsigned long long e) {
  Mat R = Mat::ident(A.n);
  while (e) {
    if (e & 1ULL) R = R * A;
    A = A * A;
    e >>= 1ULL;
  }
  return R;
}

vector<ll> mat_vec(const Mat& M, const vector<ll>& v) {
  int n = M.n;
  vector<ll> r(n, 0);
  for (int i = 0; i < n; i++) {
    __int128 acc = 0;
    for (int j = 0; j < n; j++) if (M.a[i][j]) {
      acc += (__int128)M.a[i][j] * v[j];
    }
    r[i] = (ll)(acc % MOD);
  }
  return r;
}

int main() {
    ll k; cin >> k;
    Mat A(4);
    A.a = {{3, 2, 1, 3}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}};

    A = mpow(A, k-2);

    cout << mat_vec(A, {3, 2, 1, 1})[0] << "\n";
}
