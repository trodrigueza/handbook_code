Bellman-Ford O(n*m). Pesos negativos OK.
d[v] = INF inalcanzable, -INF afectado por ciclo negativo.

struct Edge { int u, v; ll w; };

vector<ll> bellman_ford(int n, int src, vector<Edge>& es) {
    vector<ll> d(n, INF);
    d[src] = 0;
    for (int i = 0; i < n - 1; i++) {
        bool any = false;
        for (auto& [u, v, w] : es)
            if (d[u] < INF && d[u] + w < d[v]) d[v] = d[u] + w, any = true;
        if (!any) break;                      // ya convergio
    }
    for (int i = 0; i < n; i++)               // propagar -INF
        for (auto& [u, v, w] : es)
            if (d[u] < INF && (d[u] == -INF || d[u] + w < d[v]))
                d[v] = -INF;
    return d;
}

Reconstruir ciclo negativo: guardar par[v] al relajar. Tras n-1 rondas,
si (u,v) relajable: x=u; n veces x=par[x] (cae DENTRO del ciclo);
seguir par[] desde x hasta repetir x -> ese es el ciclo (invertirlo).

Camino MAS LARGO: mismo Bellman-Ford maximizando (d=-INF inicial,
relajar con >) o equivalente: negar pesos.
Ciclo (pos/neg) RELEVANTE: tras n-1 rondas, si (u,v) aun relajable,
hay ciclo que alcanza a u. Respuesta infinita <=> algun u relajable
alcanza a t (DFS desde cada u con vis compartido, o DFS en grafo
reverso desde t).
