for (int i = 0; i < 50; ++i) {
   double delta = (hi-lo)/3.0;
   double m1 = lo+delta;
   double m2 = hi-delta;
   (f(m1) > f(m2)) ? lo = m1 : hi = m2;
}
