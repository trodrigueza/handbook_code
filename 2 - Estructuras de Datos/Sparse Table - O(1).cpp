SparseTable: RMQ estático. build O(n log n), query O(1). op debe ser idempotente
(min, max, gcd, &, |). Rango [L,R] inclusivo, 0-indexado. Requiere L <= R.
uso: SparseTable<int> st(a); st.query(0, n-1);  

struct MinOp {
    template<class T>
    T operator()(const T& a, const T& b) const { return a < b ? a : b; }
};

template<class T, class Op = MinOp>
struct SparseTable {
    int n; vector<vector<T>> st; Op op;
    SparseTable() {}
    SparseTable(const vector<T>& a, Op o = Op()) { init(a, o); }
    void init(const vector<T>& a, Op o = Op()) {
        op = o; n = a.size();
        st.assign(__lg(max(n, 1)) + 1, {});
        st[0] = a;
        for (int k = 1; k < (int)st.size(); k++) {
            st[k].resize(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = op(st[k-1][i], st[k-1][i + (1 << (k-1))]);
        }
    }
    T query(int L, int R) const { // [L, R] inclusivo, 0-indexado
        int k = __lg(R - L + 1);
        return op(st[k][L], st[k][R - (1 << k) + 1]);
    }
};

