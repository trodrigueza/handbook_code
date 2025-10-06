ll gcd(ll a, ll b) {
  while(b) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}
 
ll lcm (ll a, ll b) {
  return a / gcd(a, b) * b;
}
