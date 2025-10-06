#include <bits/stdc++.h>
using namespace std;

struct Node {
  unordered_map<int, int> links;
  int suffix = 0;
  int exit = 0;
  vector<int> out;
};

class Trie {
  vector<Node> t;
  
  public:
  Trie() {
    t.emplace_back();
  }
  
  void insert(const string &s, int id) {
    int v = 0;
    for (auto ch : s) {
      if (!t[v].links.count(ch)) {
        t[v].links[ch] = (int)t.size();
        t.emplace_back();
      }
      v = t[v].links[ch];
    }
    t[v].out.push_back(id);
  }

  void build() {
    queue<int> q;
    t[0].suffix = t[0].exit = 0;
    for (auto &[ch, u] : t[0].links) {
      t[u].suffix = 0;
      t[u].exit = 0;
      q.push(u);
    }

    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto &[ch, u] : t[v].links) {
        int w = t[v].suffix;
        while (w && !t[w].links.count(ch)) w = t[w].suffix;
        if (t[w].links.count(ch)) w = t[w].links[ch];
        t[u].suffix = w;
        t[u].exit = t[w].out.empty() ? t[w].exit : w;
        q.push(u);
      }
    }
  }

  vector<long long> count_all(const string &s, int K) {
    vector<long long> cnt(K, 0);
    int v = 0;
    for (auto ch : s) {
      while (v && !t[v].links.count(ch)) v = t[v].suffix;
      if (t[v].links.count(ch)) v = t[v].links[ch];

      for (int id : t[v].out) cnt[id]++;

      for (int u = t[v].exit; u; u = t[u].exit) 
        for (int id : t[u].out) cnt[id]++;
    }
    return cnt;
  }
};

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int k;
  string s; cin >> s >> k;
  vector<string> vs(k);
  set<string> st;
  for (int i = 0; i < k; i++) {
    cin >> vs[i];
    st.insert(vs[i]);
  }

  Trie trie;
  unordered_map<string, int> mp;
  int l = 0;
  for (auto &w : st) {
    trie.insert(w, l);
    mp[w] = l;
    l++;
  }

  trie.build();
  vector<long long> ans = trie.count_all(s, (int)st.size());
  for (int i = 0; i < k; i++) {
    cout << ans[mp[vs[i]]] << " ";
  }
  cout << "\n";
}
