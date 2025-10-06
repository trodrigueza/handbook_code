int32_t main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
 
  int n; cin >> n;
  vector<int> array(n);
  for (int i = 0; i < n; i++) {
    cin >> array[i];
  }

  SparseTable St(array);

  cout << St.rsq(0, n-1) << "\n";
  cout << St.rsq(n-3, n-1) << "\n";
  
}
