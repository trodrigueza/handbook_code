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

