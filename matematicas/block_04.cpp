typedef long long ll;
const int MAX_N = 100010;
const int p = 1e9+7;
ll inv(ll a) {
  return modPow(a, p-2, p);
}
ll fact[MAX_N];

ll C(int n, int k) {
  if (n < k) return 0;
  return (((fact[n] * inv(fact[k])) % p) * inv(fact[n-k])) % p;
}

// inside int main()
  fact[0] = 1;
  for (int i = 1; i < MAX_N; ++i)
    fact[i] = (fact[i-1]*i) % p;
  cout << C(100000, 50000) << "\n";
