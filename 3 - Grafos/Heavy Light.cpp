Heavy-Light Decomposition (HLD) para arboles.
Descompone un arbol en cadenas (paths) para que las consultas de camino y subarbol
se puedan responder eficientemente usando una estructura de datos sobre un arreglo,
como un Segment Tree.

Complejidad:
- Build: O(N)
- Query en camino (u, v): O(log^2 N)
- Update en vertice v: O(log N)
- Query en subarbol de v: O(log N)

Uso general:
1. Crear instancia: HeavyLight hld(n);
2. Anadir aristas: hld.addEdge(u, v); para cada arista.
3. Construir: hld.build(root, valores_iniciales);
4. Realizar operaciones:
   - hld.updateVertex(v, nuevo_valor);
   - hld.queryPath(u, v);
   - hld.querySubtree(v);

Nota: El Segment Tree implementado es para sumas. Se puede modificar para otras
operaciones conmutativas (min, max, gcd, xor, etc.). Los nodos del arbol
son 1-indexados en la interfaz publica.

using ll = long long;

struct SegTree {
    int n;
    vector<ll> st;
    SegTree(int _n=0){ init(_n); }
    void init(int _n){
        n = 1;
        while(n < _n) n <<= 1;
        st.assign(2*n, 0);
    }
    void build(const vector<ll>& arr){ // arr is 0-indexed of size <= original_n
        int m = (int)arr.size();
        init(m);
        for(int i=0;i<m;i++) st[n+i] = arr[i];
        for(int i=n-1;i>0;i--) st[i] = st[i<<1] + st[i<<1|1];
    }
    // point update: set position p (0-indexed) to value val
    void point_update(int p, ll val){
        p += n;
        st[p] = val;
        while(p >>= 1) st[p] = st[p<<1] + st[p<<1|1];
    }
    // range query on [l, r] inclusive, 0-indexed
    ll range_query(int l, int r){
        if(l>r) return 0;
        l += n; r += n;
        ll res = 0;
        while(l <= r){
            if(l & 1) res += st[l++];
            if(!(r & 1)) res += st[r--];
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

struct HeavyLight {
    int n;
    vector<vector<int>> g;
    vector<int> parent, depth, heavy, head, pos, sz;
    int curPos;
    SegTree seg;
    vector<ll> baseArray; // values in order of pos

    HeavyLight(int _n = 0){
        init(_n);
    }
    void init(int _n){
        n = _n;
        g.assign(n+1, {});
        parent.assign(n+1, 0);
        depth.assign(n+1, 0);
        heavy.assign(n+1, -1);
        head.assign(n+1, 0);
        pos.assign(n+1, 0);
        sz.assign(n+1, 0);
        curPos = 0;
    }
    void addEdge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // first dfs: compute parent, depth, subtree sizes, and heavy child
    int dfs(int v, int p){
        parent[v] = p;
        depth[v] = (p == 0 ? 0 : depth[p] + 1);
        int size = 1;
        int maxSub = 0;
        for(int c : g[v]){
            if(c == p) continue;
            int sub = dfs(c, v);
            if(sub > maxSub){
                maxSub = sub;
                heavy[v] = c;
            }
            size += sub;
        }
        sz[v] = size;
        return size;
    }

    // decompose: assign head and positions (pos from 0..n-1)
    void decompose(int v, int h){
        head[v] = h;
        pos[v] = curPos++;
        if(heavy[v] != -1){
            decompose(heavy[v], h);
        }
        for(int c : g[v]){
            if(c == parent[v] || c == heavy[v]) continue;
            decompose(c, c);
        }
    }

    // build HLD given root and initial node values (1-indexed values)
    void build(int root, const vector<ll>& values /* 1..n index used */){
        dfs(root, 0);
        curPos = 0;
        decompose(root, root);

        baseArray.assign(n, 0);
        for(int v=1; v<=n; ++v){
            baseArray[pos[v]] = values[v];
        }
        seg.build(baseArray);
    }

    // update vertex v to new value val
    void updateVertex(int v, ll val){
        seg.point_update(pos[v], val);
    }

    // query on path u->v (inclusive), here sum
    ll queryPath(int u, int v){
        ll res = 0;
        while(head[u] != head[v]){
            if(depth[head[u]] > depth[head[v]]){
                // u's head is deeper
                res += seg.range_query(pos[head[u]], pos[u]);
                u = parent[head[u]];
            } else {
                res += seg.range_query(pos[head[v]], pos[v]);
                v = parent[head[v]];
            }
        }
        // now same head: ensure u is the shallower one
        if(depth[u] > depth[v]) swap(u, v);
        res += seg.range_query(pos[u], pos[v]);
        return res;
    }

    // optional: query subtree of v (if seg built on Euler order where subtree is contiguous)
    // In this implementation pos[] maps nodes so subtree of v is [pos[v], pos[v]+sz[v]-1]
    ll querySubtree(int v){
        return seg.range_query(pos[v], pos[v] + sz[v] - 1);
    }
};

int main(){
    int n; cin >> n;
    vector<ll> val(n+1);
    for(int i=1;i<=n;i++) cin >> val[i];

    HeavyLight hld(n);
    for(int i=0;i<n-1;i++){
        int u,v; cin >> u >> v;
        hld.addEdge(u,v);
    }
    int root = 1;
    hld.build(root, val);

    int q; cin >> q;
    while(q--){
        int type; cin >> type;
        if(type == 1){
            // update: 1 v newVal
            int v; ll newVal; cin >> v >> newVal;
            hld.updateVertex(v, newVal);
        } else if(type == 2){
            // query path sum: 2 u v
            int u,v; cin >> u >> v;
            ll ans = hld.queryPath(u,v);
            cout << ans << '\n';
        } else if(type == 3){
            // optional: query subtree sum: 3 v
            int v; cin >> v;
            cout << hld.querySubtree(v) << '\n';
        } else {
            // unknown type
        }
    }
    return 0;
}
