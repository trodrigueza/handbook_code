ll Cat[MAX_N];
 // inside int main()
   Cat[0] = 1;
   for (int n = 0; n < MAX_N-1; ++n)
     Cat[n+1] = ((4*n+2)%p * Cat[n]%p * inv(n+2)) % p;
   cout << Cat[100000] << "\n";
