Realiza a^b y retorna el resultado módulo c


long long binaryExponentiation(long long a, long long b, long long c){
  if (b == 0) return 1;
  if (b % 2 == 0) {
    long long temp = binaryExponentiation(a, b/2, c);
    return (temp * temp) % c;
  } else {
    long long temp = binaryExponentiation(a, b-1, c);
    return (temp * a) % c;
  }
}
