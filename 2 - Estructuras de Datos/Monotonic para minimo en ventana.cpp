#include <bits/stdc++.h>
using namespace std;

vector<int> slidingWindowMinimum(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> result;
    deque<int> dq; // almacena índices de elementos en orden creciente
    
    // Procesar los primeros k elementos (primera ventana)
    for (int i = 0; i < k; i++) {
        // Eliminar elementos del final que son mayores o iguales al actual
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    
    // El frente siempre contiene el mínimo de la ventana actual
    result.push_back(arr[dq.front()]);
    
    // Procesar el resto de elementos
    for (int i = k; i < n; i++) {
        // Eliminar elementos que están fuera de la ventana actual
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Eliminar elementos del final que son mayores o iguales al actual
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        result.push_back(arr[dq.front()]);
    }
    
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    vector<int> minimos = slidingWindowMinimum(arr, k);
    
    for (int minimo : minimos) {
        cout << minimo << " ";
    }
    cout << "\n";
    
    return 0;
}

