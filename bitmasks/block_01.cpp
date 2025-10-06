int mask = 18;
for (int subset = mask; subset; subset = (mask & (subset - 1)))
    cout << subset << "\n";
    