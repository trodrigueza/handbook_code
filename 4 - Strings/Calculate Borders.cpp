void solve() {
  string s; cin >> s;
  int n = (int)s.size();
  vector<int> Border(n+1);
  Border[0] = -1;
  int j = -1;

  for (int i = 0; i < n; i++) {
    while (j >= 0 && s[i] != s[j])
      j = Border[j];
    j++;
    Border[i+1] = j;
  }
  int tmp = n;
  int ans = -1;
  while (Border[tmp] > 0 && ans == -1) { 
    for (int i = 0; i < n; i++) {
      if (Border[i] == Border[tmp]) {
        ans = Border[i];
        break;
      }
    }
    tmp = Border[tmp];
  }
  if (ans == -1) {
    cout << "Just a legend\n";
    return;
  }
  for (int i = 0; i < ans; i++)
    cout << s[i];
  cout << "\n";
}
