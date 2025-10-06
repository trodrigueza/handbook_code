template<class Integer, class F>
Integer find_first_false(Integer l, Integer r, F&& f) {
    l--;
    r++;
    while (r - l > 1) {
        Integer m = l + (r - l)/2;
        if (f(m)) l = m;
        else r = m;
    }
    return r; // r -> first false, l -> last true.
}
int find_position(const vector<int>& a, int x) {
    auto f = [&](int i) {
        return a[i] < x;
    };
    int n = (int)a.size();
    int pos = find_first_false(0, n - 1, f);
    if (pos == n || a[pos] != x) return n;
    return pos;
}
