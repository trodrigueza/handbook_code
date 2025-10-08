// the main routine, variable 'i' (the bitmask) has been declared earlier
for (i = 0; i < (1<<n); i++) { // for each subset, O(2^n)
    int sum = 0;
    int mask = i;
    while (mask) {
        int two_pow_j = LSOne(mask);
        int j = __builtin_ctz(two_pow_j); // this is now O(k)
        // k is the # of on bits
        // least significant bit
        // 2^j = two_pow_j, get j
        sum += l[j];
        mask -= two_pow_j;
    }
    if (sum == X) break; // the answer is found
}

***

void search(int k) {
    if (k == n) {
        // process subset
    } else {
        search(k+1);
        subset.push_back(k);
        search(k+1);
        subset.pop_back();
    }
}
