int inversions = 0;
void merge(vector<int> &vec, vector<int> left, vector<int> right) {
    int sl = left.size();
    int sr = right.size();

    int i = 0, j = 0, k = 0;
    while (i < sl && j < sr) {
        if (left[i] <= right[j]) {
            vec[k] = left[i];
            i++;
        } else {
            vec[k] = right[j];
            j++;
            inversions += (sl - i);
        }
        k++;
    }

    while (i < sl) {
        vec[k] = left[i];
        i++;
        k++;
    }
    while (j < sr) {
        vec[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr) {
    int n = arr.size();
    if (n < 2) return;
    int sl = n / 2;

    vector<int> left(arr.begin(), arr.begin() + sl);
    vector<int> right(arr.begin() + sl, arr.end());
    
    mergeSort(left);
    mergeSort(right);

    merge(arr, left, right);
}
