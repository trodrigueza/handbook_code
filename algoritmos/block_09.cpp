ll binpow(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}

int32_t main() {
  cout << binpow(2, 31) - 1; 
}
