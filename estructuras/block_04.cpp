int main() {
  vector<int> A = {18, 17, 13, 19, 15, 11, 20, 99}; // make n power of 2
  SegmentTree st(A);
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("              A is {18,17,13,19,15,11,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // 11
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // 15
                                            
  st.update(5, 5, 77); // upd A[5] to 77
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {18,17,13,19,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // remains 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // now 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // remains 15
                                            
  st.update(0, 3, 30); // upd A[0..3] to 30
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30,30,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // now 30
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // remains 15

  st.update(3, 3, 7); // upd A[3] = 7
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30, 7,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3)); // now 7
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7)); // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4)); // now 7
}
