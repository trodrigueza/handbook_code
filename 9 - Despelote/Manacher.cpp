vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = min(r - i, p[l + (r - i)]);
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

// d parkour
void solve() 
{
    int n; cin >> n;
    ll ans = n;
    vector<int> v(n);
    vector<ll> d(n-1);
    if (n == 1) {
        cout << "1\n";
        return;
    }
 
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n-1; i++) d[i] = 0;
 
    ll l = 0, r = -1;
    for (int i = 0; i < n-1; i++) {
        ll k = 1; 
        if (i <= r)  {
            k = min(d[l+r-i]+1, r-i+1);
        }

        for (; i-k >= 0 and i+k-1 < n-1;) {
            if (    (v[i-k] < v[i-k+1] and v[i+k] < v[i+k-1]) ||
                (v[i-k] > v[i-k+1] and v[i+k] > v[i+k-1])) {
                k++;
                continue;
            }
            break;
        }
        d[i] = k-1;
 
        if (i+k-1 > r) {
            l = i-k+1, r = i+k-1;
        }
    }
    for (auto a: d) ans += a;
    cout << ans << '\n';
}
