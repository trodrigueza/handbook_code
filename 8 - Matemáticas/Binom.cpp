using int64 = long long;
using i128 = __int128_t;

static inline int64 modpow(int64 a, long long e, int64 MOD){
    int64 r = 1 % MOD;
    while (e){ if (e&1) r = (__int128)r*a % MOD; a = (__int128)a*a % MOD; e >>= 1; }
    return r;
}

// 1) Combinatoria con precompute (MOD primo)
struct Comb {
    int nmax; int64 MOD;
    vector<int64> fact, ifact; // fact[i], invfact[i]
    Comb() : nmax(0), MOD(1) {}
    Comb(int N, int64 MOD_) { init(N, MOD_); }

    void init(int N, int64 MOD_){
        nmax = N; MOD = MOD_;
        fact.assign(N+1, 1); ifact.assign(N+1, 1);
        for (int i = 1; i <= N; ++i) fact[i] = (__int128)fact[i-1]*i % MOD;
        // Fermat: MOD debe ser primo
        ifact[N] = modpow(fact[N], MOD-2, MOD);
        for (int i = N; i >= 1; --i) ifact[i-1] = (__int128)ifact[i]*i % MOD;
    }
    inline int64 C(long long n, long long k) const {
        if (k < 0 || k > n) return 0;
        if (n > nmax) throw runtime_error("Comb: n>nmax"); // o amplía
        return (((__int128)fact[n] * ifact[k]) % MOD) * ifact[n-k] % MOD;
    }
    inline int64 P(long long n, long long k) const { // permutaciones nPk
        if (k < 0 || k > n) return 0;
        if (n > nmax) throw runtime_error("Comb: n>nmax");
        return (__int128)fact[n] * ifact[n-k] % MOD;
    }
    inline int64 catalan(long long n) const { // Cn = C(2n,n)/(n+1)
        if (2*n > nmax) throw runtime_error("Comb: 2n>nmax");
        int64 c = C(2*n, n);
        return (__int128)c * modpow(n+1, MOD-2, MOD) % MOD;
    }
    // multinomial: sum(ks)=n
    inline int64 multinomial(const vector<int>& ks) const {
        long long s = 0; for (int v: ks) s += v;
        int64 res = fact[s];
        for (int v: ks) res = (__int128)res * ifact[v] % MOD;
        return res;
    }
    // fila de binomiales C(n,0..n)
    inline vector<int64> binom_row(int n) const {
        vector<int64> r(n+1);
        for (int k = 0; k <= n; ++k) r[k] = C(n,k);
        return r;
    }
};

// 2) nCk con k pequeño (O(k)), MOD primo (usa inversos)
static inline int64 nCk_smallk_mod(long long n, long long k, int64 MOD){
    if (k < 0 || k > n) return 0;
    if (k > n-k) k = n-k;
    int64 num = 1, den = 1;
    for (long long i = 1; i <= k; ++i){
        num = (__int128)num * ((n - k + i) % MOD) % MOD;
        den = (__int128)den * (i % MOD) % MOD;
    }
    return (__int128)num * modpow(den, MOD-2, MOD) % MOD;
}

// 2b) nCk con k pequeño en entero exacto (sin MOD), cuidado overflow
static inline __int128 nCk_smallk_ll(long long n, long long k){
    if (k < 0 || k > n) return 0;
    if (k > n-k) k = n-k;
    __int128 r = 1;
    for (long long i = 1; i <= k; ++i) {
        r = r * (n - k + i) / i; // exacto por aritmética combinatoria
    }
    return r; // conviértelo a string si quieres imprimir seguro
}

// 3) Lucas para MOD primo p (grande o pequeño)
struct LucasPrime {
    int p; vector<int> fact, ifact;
    LucasPrime(int prime=2){ if (prime>=2) init(prime); }
    void init(int prime){
        p = prime;
        fact.assign(p, 1); ifact.assign(p, 1);
        for (int i = 1; i < p; ++i) fact[i] = (int)((1LL*fact[i-1]*i) % p);
        auto modpowi = [&](long long a, long long e){
            long long r = 1%p;
            while (e){ if (e&1) r = (r*a)%p; a = (a*a)%p; e >>= 1; }
            return (int)r;
        };
        ifact[p-1] = modpowi(fact[p-1], p-2);
        for (int i = p-1; i >= 1; --i) ifact[i-1] = (int)(1LL*ifact[i]*i % p);
    }
    inline int Csmall(int n, int k) const { // 0<=n,k<p
        if (k<0 || k>n) return 0;
        return (int)(1LL*fact[n]*ifact[k]%p*ifact[n-k]%p);
    }
    // nCk mod p con Lucas
    int C(long long n, long long k) const {
        long long res = 1;
        while (n > 0 || k > 0){
            int ni = (int)(n % p), ki = (int)(k % p);
            if (ki > ni) return 0;
            res = (res * Csmall(ni, ki)) % p;
            n /= p; k /= p;
        }
        return (int)res;
    }
};

// 4) Pascal para N chico (O(N^2))
static inline vector<vector<int64>> pascal(int N, int64 MOD){
    vector<vector<int64>> C(N+1, vector<int64>(N+1, 0));
    for (int i = 0; i <= N; ++i){
        C[i][0] = C[i][i] = 1 % MOD;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
    return C;
}

// 5) coeficientes (a+b)^n: devuelve C(n,k)*a^(n-k)*b^k mod
static inline vector<int64> binomial_expand_powers(int n, int64 a, int64 b, int64 MOD, const Comb& comb){
    vector<int64> coeff(n+1);
    int64 ap = 1, bp = 1, inva = 0; // usaremos potencia directa
    // calc a^(n), luego ir bajando multiplicando por inv(a) si a y MOD son coprimos.
    int64 a_n = modpow(a%MOD, n, MOD);
    coeff[0] = (__int128)comb.C(n,0) * a_n % MOD;
    int64 cur = coeff[0];
    for (int k = 0; k < n; ++k){
        // C(n,k+1) = C(n,k) * (n-k)/(k+1)
        int64 nextC = (__int128)comb.C(n,k+1) % MOD; // ya O(1)
        // Recomputar término: next = C(n,k+1) * a^(n-k-1) * b^(k+1)
        // Podemos ir multiplicando por b * inv(a) si a invertible.
        // Para no depender de inversos, simplemente usamos potencias directas:
    }
    // versión simple sin optimizar potencias:
    for (int k = 0; k <= n; ++k){
        int64 ak = modpow(a%MOD, n-k, MOD);
        int64 bk = modpow(b%MOD, k, MOD);
        coeff[k] = (__int128)comb.C(n,k) * ak % MOD * bk % MOD;
    }
    return coeff;
}

// 6) Binomio con n negativo: C(-m,k) = (-1)^k C(m+k-1,k)
static inline int64 C_negativeN(long long negN, long long k, const Comb& comb){
    // negN = -m, m>0
    long long m = -negN;
    int64 val = comb.C(m + k - 1, k);
    if (k & 1) val = (comb.MOD - val) % comb.MOD;
    return val;
}

int main(){
    const long long MOD = 1'000'000'007LL;
    Comb C(1'000'000, MOD);           // precompute hasta 1e6

    // 1) nCk rápido:
    cout << C.C(10,3) << "\n";        // 120

    // 2) k pequeño:
    cout << nCk_smallk_mod(1'000'000'000'000LL, 5, MOD) << "\n";

    // 3) Lucas (p primo pequeño):
    LucasPrime L(1'000'003);          // p ~ 1e6+3
    cout << L.C(1234567890123LL, 54321) << "\n";

    // 4) Pascal:
    auto P = pascal(5, MOD);          // C(5,2)=10
    cout << P[5][2] << "\n";

    // 5) coeficientes de (a+b)^n:
    auto cf = binomial_expand_powers(5, 2, 3, MOD, C); // coef[k]=C(5,k)*2^(5-k)*3^k
    cout << cf[2] << "\n";           // C(5,2)*2^3*3^2

    // 6) n negativo:
    // C(-7, 3) = (-1)^3 C(7+3-1, 3) = -C(9,3) mod MOD
    cout << C_negativeN(-7, 3, C) << "\n";
}
