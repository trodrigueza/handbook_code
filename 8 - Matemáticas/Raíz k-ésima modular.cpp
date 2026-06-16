// ============================================================
//  Raíz k-ésima discreta — discrete_root
//
//  Resuelve x^k ≡ a (mod p), con p primo.
//
//  Prerequisitos
//    ll = long long
//    Las funciones power, inverse, gcd deben estar disponibles.
//    inverse(a, p) debe ser el inverso modular via Euclidiano extendido.
//
//  discrete_root(k, a, p) → cualquier x tal que x^k ≡ a (mod p)
//                           retorna -1 si no existe solución
//                           convención: 0^0 = 1
//
//  Complejidad: O(p^(1/4)) esperado (baby-step giant-step interno)
//
//  Teoría
//    Se reduce x^k ≡ a (mod p) usando que el grupo (Z/pZ)* es cíclico.
//    Se factoriza g = gcd(k, p-1) y se resuelve por cada factor primo
//    de g via peth_root (Adleman-Manders-Miller generalizado con BSGS).
// ============================================================

// Cuenta pasos hasta llegar a 1 aplicando x -> x^base mod p
int cnt(ll a, ll base, ll p) {
    int ret = 0;
    while (a != 1) { a = power(a, base, p); ++ret; }
    return ret;
}

// Resuelve x^(p^e) ≡ a (mod mod), con p primo y mod primo
ll peth_root(ll a, ll p, int e, ll mod) {
    ll q = mod - 1;
    int s = 0;
    while (q % p == 0) { q /= p; ++s; }

    ll pe  = power(p, e, mod);
    ll ans = power(a, ((pe - 1) * inverse(q, pe) % pe * q + 1) / pe, mod);
    ll c   = 2;
    while (power(c, (mod - 1) / p, mod) == 1) ++c;
    c = power(c, q, mod);

    map<ll, int> mp;
    ll add = 1;
    int v  = (int)sqrt((double)(s - e) * p) + 1;
    ll mul = power(c, v * power(p, s - 1, mod - 1) % (mod - 1), mod);
    for (int i = 0; i <= v; ++i) {
        mp[add] = i;
        add = add * mul % mod;
    }

    mul = inverse(power(c, power(p, s - 1, mod - 1), mod), mod);
    for (int i = e; i < s; ++i) {
        ll err    = inverse(power(ans, pe, mod), mod) * a % mod;
        ll target = power(err, power(p, s - 1 - i, mod - 1), mod);
        for (int j = 0; j <= v; ++j) {
            if (mp.find(target) != mp.end()) {
                int x = mp[target];
                ans = ans * power(c, (j + v * x) * power(p, i - e, mod - 1) % (mod - 1), mod) % mod;
                break;
            }
            target = target * mul % mod;
            assert(j != v);
        }
    }
    return ans;
}

// Retorna x tal que x^k ≡ a (mod p), p primo. -1 si no existe.
ll discrete_root(ll k, ll a, ll p) {
    if (k > 0 && a == 0) return 0;
    k %= p - 1;
    ll g = gcd(k, p - 1);
    if (power(a, (p - 1) / g, p) != 1) return -1;
    a = power(a, inverse(k / g, (p - 1) / g), p);
    for (ll div = 2; div * div <= g; ++div) {
        int sz = 0;
        while (g % div == 0) { g /= div; ++sz; }
        if (sz > 0) a = peth_root(a, div, sz, p);
    }
    if (g > 1) a = peth_root(a, g, 1, p);
    return a;
}
