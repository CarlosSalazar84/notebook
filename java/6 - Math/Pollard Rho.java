La función Rho de Pollard calcula un divisor no trivial de n.
IMPORTANTE: Deben agregarse Modular Multiplication y Greatest common divisor para long.

public static long rho(long n) {
    if ((n&1)==0) return 2;
    long i = 0, k = 2, x = 3, y = 3, d;
    while (true) {
        x = (modmul(x, x, n) + n - 1) % n;
        d = gcd(Math.abs(y - x), n);
        if (d != 1 && d != n) return d;
        if (++i == k) { y = x; k <<= 1; }
    }
}
