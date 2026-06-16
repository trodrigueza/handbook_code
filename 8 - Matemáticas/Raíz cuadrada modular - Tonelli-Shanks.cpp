// ============================================================
//  Raíz cuadrada modular — Tonelli-Shanks
//
//  Resuelve x² ≡ a (mod p), con p primo impar.
//
//  Prerequisitos
//    ll  = long long
//    lll = __int128   (para productos intermedios sin overflow)
//
//  power(a, e, m)         → aᵉ mod m  (exponenciación rápida)
//  tonelliShanks(a, p)    → x tal que x² ≡ a (mod p)
//                           retorna -1 si a no es residuo cuadrático
//                           retorna  0 si a ≡ 0 (mod p)
//
//  Complejidad: O(log² p) esperado
//
//  Teoría
//    Un entero a es residuo cuadrático mod p  ⟺  a^((p-1)/2) ≡ 1 (mod p)
//    (criterio de Euler).  Si p ≡ 3 (mod 4), la raíz es directamente
//    a^((p+1)/4) mod p.  En otro caso se usa el algoritmo de Tonelli-
//    Shanks: se factoriza p-1 = Q·2^S y se itera reduciendo la potencia
//    de 2 en el orden del residuo hasta llegar a 1.
//
//  Nota: si p admite DOS raíces {x, p-x}, esta función devuelve la menor.
//        Para obtener ambas: r = tonelliShanks(a, p);  otra = p - r;
// ============================================================
ll power(ll a, ll e, ll m) {
    a %= m;
    if (a < 0) a += m;
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = (lll)r * a % m;
        a = (lll)a * a % m;
        e >>= 1;
    }
    return r;
}

// Devuelve una raíz de x^2 ≡ a (mod p), o -1 si no existe (p primo impar)
ll tonelliShanks(ll a, ll p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return 0;
    if (p == 2) return a;

    if (power(a, (p - 1) / 2, p) != 1) return -1; // no es RC

    if (p % 4 == 3)
        return power(a, (p + 1) / 4, p);

    // p - 1 = Q  * 2^S
    ll Q = p - 1, S = 0;
    while (Q % 2 == 0) { Q /= 2; S++; }

    // Buscar no-residuo z
    ll z = 2;
    while (power(z, (p - 1) / 2, p) != p - 1) z++;

    ll M = S;
    ll c = power(z, Q, p);
    ll t = power(a, Q, p);
    ll R = power(a, (Q + 1) / 2, p);

    while (t != 1) {
        ll i = 0, t2i = t;
        while (t2i != 1) {
            t2i = (lll)t2i * t2i % p;
            i++;
        }
        ll b = power(c, 1LL << (M - i - 1), p);
        M = i;
        c = (lll)b * b % p;
        t = (lll)t * c % p;
        R = (lll)R * b % p;
    }
    return R;
}
