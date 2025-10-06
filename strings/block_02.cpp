#include <bits/stdc++.h>
using namespace std;
 
struct Node {
  int links[26];
  int suffix;
  int exit;
  vector<int> out;
 
  Node() {
    fill(begin(links), end(links), -1);
    suffix = exit = -1;
  }
};
 
class Trie {
  vector<Node> t;
 
  public:
    Trie() {
      t.emplace_back();
    }
 
    void insert(const string& s, int id) {
      int v = 0;
      for (char ch : s) {
        int c = ch - 'a';
        if (t[v].links[c] == -1) {
          t[v].links[c] = (int)t.size();
          t.emplace_back();
        }
        v = t[v].links[c];
      }
      t[v].out.push_back(id);
    }
 
    void build() {
      queue<int> q;
      t[0].suffix = t[0].exit = 0;
      
      for (int c = 0; c < 26; c++) {
        int u = t[0].links[c];
        if (u != -1) {
          t[u].suffix = 0;
          t[u].exit = 0;
          q.push(u);
        } else {
          t[0].links[c] = 0;
        }
      }
 
      while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int c = 0; c < 26; c++) {
          int u = t[v].links[c];
          if (u == -1) {
            t[v].links[c] = t[t[v].suffix].links[c];
            continue;
          }
          t[u].suffix = t[t[v].suffix].links[c];
          t[u].exit = t[t[u].suffix].out.empty() ? t[t[u].suffix].exit : t[u].suffix;
          q.push(u);
        }
      }
    }
 
    vector<long long> countAll(const string &s, int K) {
      vector<long long> cnt(K, 0);
      int v = 0;
      for (char ch : s) {
        v = t[v].links[ch-'a'];
        for (int i : t[v].out) cnt[i]++;
 
        for (int u = t[v].exit; u; u = t[u].exit) {
          for (int i : t[u].out) cnt[i]++;
        }
      }
      return cnt;
    }
};
 
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
 
  string s; cin >> s;
  int k; cin >> k;
  Trie trie;
  set<string> st;
  vector<string> vs(k);
  for (int i = 0; i < k; i++) {
    cin >> vs[i];
    //cout << tmp << "-\n";
    st.insert(vs[i]);
  }
  
  int l = 0;
  unordered_map<string, int> mp;
  for (auto &w : st) {
    mp[w] = l;
    trie.insert(w, l);
    l++;
  }
  trie.build();
  vector<long long> ans = trie.countAll(s, st.size());
  for (int i = 0; i < k; i++) {
    cout << ans[mp[vs[i]]] << " ";
  } 
  cout << "\n";
}
