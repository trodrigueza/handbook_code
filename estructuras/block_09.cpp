const int K = 25;
const int MAXN = 1e5;
int st[K + 1][MAXN];

class SparseTable {
private:
	int n;

public:
	SparseTable(const vector<int>& array) {
		n = array.size();
		buildSparseTable(array);
	}

	void buildSparseTable(const vector<int>& array) {
		copy(array.begin(), array.end(), st[0]);
		for (int i = 1; i <= K; i++) 
			for (int j = 0; j + (1 << i) <= n; j++) 
				st[i][j] = min(st[i-1][j], st[i-1][j+(1<<(i-1))]); // f(x, y) = x + y for rsq
	}

	ll rsq(int L, int R) { // O(K) == O(logMAXN)
		ll sum = 0;
		for (int i = K; i >= 0; i--) {
			if ((1 << i) <= R - L + 1) {
				sum += st[i][L];
				L += 1 << i;
			}
		}
		return sum;
	}

	int rmq(int L, int R) {
		auto lg = [&](unsigned long long i) {
			return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
		};
		int i = lg(R - L + 1);
		int minimum = min(st[i][L], st[i][R - (1<<i) + 1]);
		return minimum;
	}
};
