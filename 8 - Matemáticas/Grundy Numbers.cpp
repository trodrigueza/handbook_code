const int N = 200000;
int G[N];

int32_t main() {
  int n1, n2, n3, k; cin >> n1 >> n2 >> n3 >> k;
  vector<int> kk(k);
  for (int i = 0; i < k; i++) {
    cin >> kk[i];
  }

  auto mex = [&](set<int> &s) {
    int i = 0;
    while (s.size() && *(s.begin()) == i) {s.erase(s.begin()); i++;}
    return i;
  };

  // calculate Grundy Numbers
  G[0] = 0;
  for (int i = 1; i < N; i++) {
    set<int> s;
    for (int j = 0; j < k; j++) {
      if (i - kk[j] < 0) continue;
      s.insert(G[i - kk[j]]); // valid jumps
    }
    if (s.empty()) G[i] = 0;
    else G[i] = mex(s);
  }

  cout << ((G[n1] ^ G[n2] ^ G[n3]) ? "Peter" : "Vasya") << "\n";
  #ifdef ONPC
  cerr << endl << "finished in " << clock() * 1.0 / CLOCKS_PER_SEC << " sec" << endl;
  #endif
}
