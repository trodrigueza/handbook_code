class SegmentTree {
private:
	int n;
	vector<int> A, st, lazy;

	int l(int p) { return p<<1; } // left child
	int r(int p) { return (p<<1)+1; } // right child

	int conquer(int a, int b) {
		if (a == -1) return b; // corner case
		if (b == -1) return a;
		return min(a, b); // RMQ
	}

	void build(int p, int L, int R) {
		if (L == R) st[p] = A[L]; // base case
		else {
			int m = L+(R-L)/2;
			build(l(p), L, m);
			build(r(p), m+1, R);
			st[p] = conquer(st[l(p)], st[r(p)]);
		}
	}

	void propagate(int p, int L, int R) {
		if (lazy[p] != -1) { // has lazy flag
			st[p] = lazy[p]; // [L..R] has same value
			if (L != R)  // not a leaf
				lazy[l(p)] = lazy[r(p)] = lazy[p]; // prop down
			else // L == R, a single index
				A[L] = lazy[p]; // update
			lazy[p] = -1; // erase flag
		}
	}

	int RMQ(int p, int L, int R, int i, int j) {
		propagate(p, L, R); // lazy prop
		if (i > j) return -1;
		if ((L >= i) && (R <= j)) return st[p]; // found seg
		int m = L+(R-L)/2;
		return conquer(RMQ(l(p), L, m, i, min(m, j)),
									RMQ(r(p), m+1, R, max(i, m+1), j));
	}

	void update(int p, int L, int R, int i, int j, int val) {
		propagate(p, L, R); // lazy prop
		if (i > j) return;
		if ((L >= i) && (R <= j)) { // found seg
			lazy[p] = val; // update
			propagate(p, L, R); // lazy prop
		} else {
			int m = L+(R-L)/2;
			update(l(p), L, m, i, min(m, j), val);
			update(r(p), m+1, R, max(i, m+1), j, val);
			int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
			int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
			st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
		}
	}

public:
	SegmentTree(int sz) : n(sz), st(4*n), lazy(4*n, -1) {}

	SegmentTree(const vector<int> &initialA) : SegmentTree((int)initialA.size()) {
		A = initialA;
		build(1, 0, n-1);
	}

	void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

	int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }
};

int main() {
  vector<int> A = {18, 17, 13, 19, 15, 11, 20, 99}; // make n power of 2
  SegmentTree st(A);
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("              A is {18,17,13,19,15,11,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // 11
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // 15

  st.update(5, 5, 77); // upd A[5] to 77
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {18,17,13,19,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // remains 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // now 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // remains 15

  st.update(0, 3, 30); // upd A[0..3] to 30
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30,30,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // now 30
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // remains 15

  st.update(3, 3, 7); // upd A[3] = 7
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30, 7,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // now 7
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // now 7
}
