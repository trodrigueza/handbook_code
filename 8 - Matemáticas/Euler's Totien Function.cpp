int EulerPh[MAX_N+10];
for (int i = 1; i <= MAX_N; ++i) EulerPh[i] = i;
for (int i = 2; i <= MAX_N; ++i)
  if (EulerPh[i] == i)
    for (int j = i; j <= MAX_N; j += i)
      EulerPh[j] = (EulerPh[j]/i) * (i-1);
