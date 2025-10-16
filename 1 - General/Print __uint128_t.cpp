* Esta funcion imprime un entero sin signo de 128 bits (__uint128_t) en su representacion decimal convirtiendo el número a una cadena de caracteres.

int print_uint128(__uint128_t n) {
  if (n == 0)  return printf("0\n");
  char str[40] = {0}; // log10(1 << 128) + '\0'
  char *s = str + sizeof(str) - 1;
  while (n != 0) {
    if (s == str) return -1; // never happens
    *--s = "0123456789"[n % 10]; /
    n /= 10;
  }
  return printf("%s\n", s);
}
