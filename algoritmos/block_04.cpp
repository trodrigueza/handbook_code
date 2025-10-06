void countingSort(int arr[], int min, int max, int n) {
    int k = max - min + 1;
    int counts[k], sorted[n];
    memset(counts, 0, sizeof(counts));
    for (int i = 0; i < n; i++)
        counts[arr[i] - min]++;
        
    for (int i = 1; i < k; i++)
        counts[i] += counts[i - 1];
        
    for (int i = n-1; i >=0 ; i--) {
        sorted[counts[arr[i] - min] - 1] = arr[i];
        counts[arr[i] - min]--;
    }
    
    for (int i = 0; i < n; i++) 
        arr[i] = sorted[i];
}
