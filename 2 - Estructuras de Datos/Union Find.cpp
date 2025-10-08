class UnionFind {
private:
	vector<int> p, rank, setSize;
	int numSets;
public:
	UnionFind(int N) {
		p.assign(N, 0); iota(p.begin(), p.end(), 0);
		rank.assign(N, 0);
		setSize.assign(N, 1);
		numSets = N;
	}

	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	int numDisjointSets() { return numSets; }
	int sizeOfSet(int i) { return setSize[findSet(i)]; }

	void unionSet(int i, int j) {
		if (isSameSet(i, j)) return;
		int x = findSet(i), y = findSet(j);
		if (rank[x] > rank[y]) swap(x, y);
		p[x] = y;
		if (rank[x] == rank[y]) ++rank[y];
		--numSets;
		setSize[y] += setSize[x];
	}
};

int32_t main() {
  UnionFind UF(5);
}

* Permite mantener una colección de conjuntos disyuntos. find(u) indica a qué conjunto pertenece u. unite(u, v) une los conjuntos de u y v en uno.

struct dsu {
    vector<int> par, sz;
    int size; // Cantidad de conjuntos

    dsu(int n) : par(n), sz(n, 1) {
        size = n;
        iota(par.begin(), par.end(), 0);
    }
    // Busca el nodo representativo del conjunto de u
    int find(int u) {
        return par[u] == u ? u : (par[u] = find(par[u]));
    }
    // Une los conjuntos de u y v
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (sz[u] > sz[v]) swap(u, v);
        par[u] = v;
        sz[v] += sz[u];
        size--;
    }
    // Cantidad de elementos en el conjunto de u
    int count(int u) { return sz[find(u)]; }
};
