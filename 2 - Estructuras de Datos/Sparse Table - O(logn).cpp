* Construcción O(n log n). Guarda en st[k][i] la suma del bloque de longitud 2^k que empieza en i.
Consulta: descompón [L,R] en bloques disjuntos de potencias de dos.

struct SparseTableSum {
    int n, K;
    vector<vector<long long>> st;

    SparseTableSum() {}
    SparseTableSum(const vector<long long>& a){ init(a); }

    void init(const vector<long long>& a){
        n = (int)a.size();
        K = 1; while ((1 << K) <= n) ++K;
        st.assign(K, vector<long long>(n));
        st[0] = a;
        for (int k = 1; k < K; ++k)
            for (int i = 0; i + (1 << k) <= n; ++i)
                st[k][i] = st[k-1][i] + st[k-1][i + (1 << (k-1))];
    }

    // suma en [L,R] (0-index)
    long long query(int L, int R) const {
        long long ans = 0;
        for (int k = K - 1; k >= 0; --k) {
            if ((1 << k) <= R - L + 1) {
                ans += st[k][L];
                L += 1 << k;
            }
        }
        return ans;
    }
};

int main(){
    int n; cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    SparseTableSum rsq(a);
    int L, R; cin >> L >> R;
    cout << rsq.query(L, R) << "\n";
}
