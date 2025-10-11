⁠ #include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Precomputamos los conteos acumulados por bit
    const int B = 64;
    vector<vector<int>> pref(B, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++) {
        for (int b = 0; b < B; b++) {
            pref[b][i + 1] = pref[b][i] + ((a[i] >> b) & 1);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; // a índices 0-based
        vector<int> cnt(B);
        for (int b = 0; b < B; b++) {
            cnt[b] = pref[b][r] - pref[b][l];
        }

        // Mostrar los 64 conteos
        for (int b = 0; b < B; b++) {
            cout << cnt[b] << (b + 1 == B ? '\n' : ' ');
        }
    }
    return 0;
}
