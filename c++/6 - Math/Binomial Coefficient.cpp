Calcula el coeficiente binomial nCr, entendido como el número de subconjuntos de r elementos escogidos de un conjunto con n elementos.

long long ncr(long long n, long long r) {
    if (r < 0 || n < r) return 0;
    r = min(r, n - r);
    long long ans = 1;
    for (int i = 1; i <= r; i++) {
        ans = ans * (n - i + 1) / i;
    }
    return ans;
}
