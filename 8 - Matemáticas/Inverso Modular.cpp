ll mod_pow(ll a, ll b, ll m) {
  ll res = 1;
  a %= m;
  while (b > 0) {
    if (b & 1)
      res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

ll mod_inverse(ll a, ll m) {
  return mod_pow(a, m - 2, m); // only valid if m is prime
}
