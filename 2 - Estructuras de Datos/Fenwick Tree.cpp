* La clase principal FenwickTree soporta actualizaciones de punto y consultas de rango (PURQ).
Adicionalmente, se incluyen dos clases auxiliares que usan el arbol de Fenwick:
- RUPQ: para actualizaciones de rango y consultas de punto.
- RURQ: para actualizaciones de rango y consultas de rango.

#define LSOne(S) ((S) & -(S))

class FenwickTree {
private:
	vector<ll> ft;
public:
	FenwickTree(int m) { ft.assign(m + 1, 0); } // empty FT

	void build(const vector<ll> &f) {
		int m = (int)f.size() - 1; // f[0] = 0
		ft.assign(m + 1, 0);
		for (int i = 1; i <= m; ++i) {
			ft[i] += f[i];
			if (i + LSOne(i) <= m)
				ft[i + LSOne(i)] += ft[i];
		}
	}

	FenwickTree(const vector<ll> &f) { build(f); } // FT based on f

	FenwickTree(int m, const vector<int> &s) { // FT based on s
		vector<ll> f(m + 1, 0);
		for (int i = 0; i < (int)s.size(); ++i)
			++f[s[i]];
		build(f);
	}

	ll rsq(int j) { // RSQ(1, j)
		ll sum = 0;
		for (; j; j -= LSOne(j))
			sum += ft[j];
		return sum;
	}

	ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); }

	void update(int i, ll v) {
		for (; i < (int)ft.size(); i += LSOne(i))
			ft[i] += v;
	}

	int select(ll k) { // min i such that RSQ(1, i) >= k
		int lo = 1, hi = ft.size() - 1;
		for (int i = 0; i < 30; i++) {
			int mid = lo + (hi - lo) / 2;
			(rsq(1, mid) < k) ? lo = mid : hi = mid;
		}
		return hi;
	}
};

class RUPQ {
private:
	FenwickTree ft; // Internally PURQ FT
public:
	RUPQ(int m) : ft(FenwickTree(m)) {}

	void range_update(int ui, int uj, ll v) {
		ft.update(ui, v); // [ui, ui+1, ..., m] + v
		ft.update(uj + 1, -v); // [uj+1, uj+2, ..., m] - v
	} // [ui, ui+1, ..., uj] + v

	ll point_query(int i) { return ft.rsq(i); }
};

class RURQ {
private: // needs two helper FTs
	RUPQ rupq; // one RUPQ
	FenwickTree purq; // one PURQ
public:
	RURQ(int m) : rupq(RUPQ(m)), purq(FenwickTree(m)) {}

	void range_update(int ui, int uj, ll v) {
		rupq.range_update(ui, uj, v); // [ui, ui+1, ...,uj] + v
		purq.update(ui, v * (ui - 1));
		purq.update(uj + 1, -v * uj);
	}

	ll rsq(int j) {
		return rupq.point_query(j)*j - purq.rsq(j);
	}

	ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); }
};

int32_t main() {
  vector<ll> f = {0,0,1,0,1,2,3,2,1,1,0};
  FenwickTree ft(f);
  printf("%lld\n", ft.rsq(1, 6)); // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%d\n", ft.select(7)); // index 6, rsq(1, 6) == 7, which is >= 7
  ft.update(5, 1); // update demo -> ft[5] + 1, ft[6] + 1, ft[8] + 1
  printf("%lld\n", ft.rsq(1, 10)); // now 12 => ft[10] + ft[8]
  printf("=====\n");
  RUPQ rupq(10);
  RURQ rurq(10);
  rupq.range_update(2, 9, 7); // [2, 3, ..., 9] + 7
  rurq.range_update(2, 9, 7);
  rupq.range_update(6, 7, 3); // 6&7 + 3 (10)
  rurq.range_update(6, 7, 3);
  // idx = 0 (unused) | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10
  // val = -          | 0 | 7 | 7 | 7 | 7 |10 |10 | 7 | 7 | 0
  for (int i = 1; i <= 10; i++)
    printf("%d -> %lld\n", i, rupq.point_query(i));

  printf("RSQ(1, 10) = %lld\n", rurq.rsq(1, 10)); // 62
  printf("RSQ(6, 7) = %lld\n", rurq.rsq(6, 7)); // 20
}
