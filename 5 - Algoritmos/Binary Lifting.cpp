// Doubling (binary lifting) para saltar K veces una función next[i].
// Maneja -1 como "sin siguiente".
#include <bits/stdc++.h>
using namespace std;

struct Doubling {
    int n, LOG;
    vector<vector<int>> up; // up[k][i] = adónde llego desde i tras 2^k saltos

    // next[i] en 0-index; si no hay siguiente: -1.
    Doubling(const vector<int>& next, long long K_max) {
        n = (int)next.size();
        LOG = 1;
        while ((1LL << LOG) <= K_max) ++LOG;
        up.assign(LOG, vector<int>(n, -1));
        for (int i = 0; i < n; ++i) up[0][i] = next[i];
        for (int k = 0; k + 1 < LOG; ++k) {
            for (int i = 0; i < n; ++i) {
                int mid = up[k][i];
                up[k+1][i] = (mid == -1 ? -1 : up[k][mid]);
            }
        }
    }

    // Aplica K saltos desde s; devuelve -1 si "muere" antes.
    int jump(int s, long long K) const {
        int cur = s;
        for (int k = 0; k < LOG && cur != -1; ++k) {
            if (K & (1LL << k)) cur = up[k][cur];
        }
        return cur;
    }
};
