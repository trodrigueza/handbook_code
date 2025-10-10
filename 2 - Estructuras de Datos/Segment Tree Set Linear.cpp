#include <bits/stdc++.h>
using namespace std;

#define int long long

// Quiero sumar 1, 2, 3, ... en ai, ai+1, a+2, ...
// Esto es, sumar p - i + 1 donde p es el índice..
// Esto es, sumar Ap + B, una funció lineal.......
// con A = 1 y B = 1 - i
// También necesito poder hacer ai = ai+1 = ai+2 = k
const int MAXN = 100005;
const int T = 26;
int st[T][4*MAXN]; // suma del segmento
int addA[T][4*MAXN]; // A
int addB[T][4*MAXN]; // B
bool hasSet[T][4*MAXN]; // toca hacer = k
int setVal[T][4*MAXN]; // valor de k

void build(int t, int v, int tl, int tr, const vector<int> &a) {
    addA[t][v] = addB[t][v] = hasSet[t][v] = setVal[t][v] = 0;
    if (tl == tr) {
        st[t][v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(t, v*2, tl, tm, a);
        build(t, v*2+1, tm+1, tr, a);
        st[t][v] = st[t][v*2] + st[t][v*2+1];
    }
}

// suma de índices p en [L..R], 0-based
inline int sumIdx(int l, int r) {
    if (l > r) return 0;
    int len = r - l + 1;
    return (l + r) * len / 2;
}

// Nodo v ([tl, tr]) -> k
inline void applySet(int t, int v, int tl, int tr, int val) {
    int len = (tr - tl + 1);
    st[t][v] = val * len;
    hasSet[t][v] = 1;
    setVal[t][v] = val;
    addA[t][v] = 0;
    addB[t][v] = 0;
}

// Nodo v ([tl, tr]) -> A*p + B
inline void applyAddLinear(int t, int v, int tl, int tr, int A, int B) {
    int len = (tr - tl + 1);
    st[t][v] += A * sumIdx(tl, tr) + B * len;
    addA[t][v] += A;
    addB[t][v] += B;
}

void push(int t, int v, int tl, int tr) {
    if (tl == tr) {
        if (hasSet[t][v]) {hasSet[t][v] = 0;}
        addA[t][v] = 0; addB[t][v] = 0;
        return;
    }
    int tm = (tl + tr) / 2;
    int L =v* 2, R = v*2+1;
    if (hasSet[t][v]) {
        applySet(t, L, tl, tm, setVal[t][v]);
        applySet(t, R, tm+1, tr, setVal[t][v]);
        hasSet[t][v] = 0;
    }

    if (addA[t][v] != 0 || addB[t][v] != 0) {
        applyAddLinear(t, L, tl, tm, addA[t][v], addB[t][v]);
        applyAddLinear(t, R, tm+1, tr, addA[t][v], addB[t][v]);
        addA[t][v] = 0;
        addB[t][v] = 0;
    }
}

void updateAddLinear(int t, int v, int tl, int tr, int l, int r, int A, int B) {
    if (l > r) return;
    if (l == tl && r == tr) {
        applyAddLinear(t, v, tl, tr, A, B);
    } else {
        push(t, v, tl, tr);
        int tm = (tl + tr) / 2;
        updateAddLinear(t, v*2, tl, tm, l, min(r, tm), A, B);
        updateAddLinear(t, v*2+1, tm+1, tr, max(l, tm+1), r, A, B);
        st[t][v] = st[t][v*2] + st[t][v*2+1];
    }
}

// suma constante
void updateRange(int t, int v, int tl, int tr, int l, int r, int add_val) {
    updateAddLinear(t, v, tl, tr, l, r, 0, add_val);
}

// suma 1,2,3,...,(r-l+1) en [l..r]
void updateArithmeticInc(int t, int v, int tl, int tr, int l, int r) {
    updateAddLinear(t, v, tl, tr, l, r, 1, 1 - l);
}

// a[i] = val para i en [l..r]
void updateSet(int t, int v, int tl, int tr, int l, int r, int val) {
    if (l > r) return;
    if (l == tl && r == tr) {
        applySet(t, v, tl, tr, val);
    } else {
        push(t, v, tl, tr);
        int tm = (tl + tr) / 2;
        updateSet(t, v*2, tl, tm, l, min(r, tm), val);
        updateSet(t, v*2+1, tm+1, tr, max(l, tm+1), r, val);
        st[t][v] = st[t][v*2] + st[t][v*2+1];
    }
}

// suma en [l..r]
int queryRange(int t, int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return st[t][v];
    push(t, v, tl, tr);
    int tm = (tl + tr) / 2;
    return queryRange(t, v*2, tl, tm, l, min(r, tm)) + queryRange(t, v*2+1, tm+1, tr, max(l, tm+1), r);
}

int32_t main() {
    int n, q; cin >> n >> q;
    string s; cin >> s;

    for (int i = 0; i < 26; i++) {
        vector<int> a(n, 0);
        for (int j = 0; j < n; j++)
            if (s[j] - 'a' == i) a[j] = 1;
        build(i, 1, 0, n-1, a);
    }

    while (q--) {
        int i, j, k; cin >> i >> j >> k;
        i--; j--;

        if (k) {
            int l = i;
            for (int c = 0; c < 26; c++) {
                int cnt = queryRange(c, 1, 0, n-1, i, j);
                if (!cnt) continue;
                updateSet(c, 1, 0, n-1, i, j, 0);
                updateSet(c, 1, 0, n-1, l, l+cnt-1, 1);
                l += cnt;
            }
        } else {
            int l = i;
            for (int c = 25; c >= 0; c--) {
                int cnt = queryRange(c, 1, 0, n-1, i, j);
                if (!cnt) continue;
                updateSet(c, 1, 0, n-1, i, j, 0);
                updateSet(c, 1, 0, n-1, l, l+cnt-1, 1);
                l += cnt;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++)
            if (queryRange(c, 1, 0, n-1, i, i))
                cout << char('a' + c);
    }
    cout << "\n";
}
