#include <bits/stdc++.h>
// the main routine
int i, n = 8, p[8] = {0, 1, 2, 3, 4, 5, 6, 7};
do { // the  first permutation
// try all n! permutations
// test each permutation 'p' in O(m)
} while (next_permutation(p, p+n)); // complexity = O(n! * m)

*****

void search() {
    if (permutation.size() == n) {
        // process permutation
    } else {
        for (int i = 0; i < n; i++) {
            if (chosen[i]) continue;
            chosen[i] = true;
            permutation.push_back(i);
            search();
            chosen[i] = false;
            permutation.pop_back();
        }
    }
}
