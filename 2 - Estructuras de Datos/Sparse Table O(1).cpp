* Válida para min, max, gcd, lcm, AND, OR, XOR...
* Construcción O(n log n); consulta O(1) con 2 bloques solapados.
* Para gcd/lcm, define un Op con std::gcd/std::lcm (C++17). Para XOR, usa [](T a,T b){return a^b;}.

// Functor de ejemplo (min). Puedes definir Max, GCD, etc.
struct MinOp {
    template<class T>
    T operator()(const T& a, const T& b) const { return a < b ? a : b; }
};

template<class T, class Op = MinOp>
struct SparseTableIdem {
    int n, K;
    vector<int> lg;             // lg[i] = floor(log2(i))
    vector<vector<T>> st;       // st[k][i] cubre [i, i+2^k-1]
    Op op;

    SparseTableIdem() {}
    SparseTableIdem(const vector<T>& a, Op op_ = Op()) { init(a, op_); }

    void init(const vector<T>& a, Op op_ = Op()) {
        op = op_;
        n = (int)a.size();
        K = 1; while ((1 << K) <= n) ++K;
        st.assign(K, vector<T>(n));
        st[0] = a;

        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

        for (int k = 1; k < K; ++k)
            for (int i = 0; i + (1 << k) <= n; ++i)
                st[k][i] = op(st[k-1][i], st[k-1][i + (1 << (k-1))]);
    }

    // Query en [L, R] (0-index, L<=R)
    T query(int L, int R) const {
        int k = lg[R - L + 1];
        return op(st[k][L], st[k][R - (1 << k) + 1]);
    }
};

// ----- ejemplo de uso -----
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    SparseTableIdem<int, MinOp> rmq(a);
    int L, R; cin >> L >> R;    // ejemplo
    cout << rmq.query(L, R) << "\n";
}
