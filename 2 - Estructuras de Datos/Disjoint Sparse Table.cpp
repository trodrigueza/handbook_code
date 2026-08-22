Disjoint Sparse Table: query O(1) para cualquier op ASOCIATIVA.
No pide idempotencia ni elemento neutro. build O(n log n), mem O(n log n).
Respeta el orden -> vale para ops NO conmutativas. [L,R] inclusivo, 0-indexado. Estatico.

struct SumOp {
    template<class T>
    T operator()(const T& a, const T& b) const { return a + b; }
};

template<class T, class Op = SumOp>
struct DisjointSparseTable {
    int n; vector<vector<T>> t; Op op;
    DisjointSparseTable() {}
    DisjointSparseTable(const vector<T>& a, Op o = Op()) { init(a, o); }

    void init(const vector<T>& a, Op o = Op()) {
        op = o; n = (int)a.size();
        int K = n > 1 ? __lg(n - 1) + 1 : 1;
        t.assign(K, vector<T>(n));
        t[0] = a;
        for (int k = 1; k < K; k++) {
            int half = 1 << k, len = half << 1;
            for (int c = half; c < n; c += len) {
                t[k][c] = a[c];                                 
                for (int j = c + 1; j < min(n, c + half); j++)
                    t[k][j] = op(t[k][j-1], a[j]);
                t[k][c-1] = a[c-1];                              
                for (int j = c - 2; j >= c - half; j--)
                    t[k][j] = op(a[j], t[k][j+1]);
            }
        }
    }

    T query(int L, int R) const {        
        if (L == R) return t[0][L];
        int k = __lg(L ^ R);
        return op(t[k][L], t[k][R]);
    }
};
