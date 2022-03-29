/**
Calcula la sumatoria de (a * i + b) % n de 0 a n
O(log(n))
**/
ll f(ll a, ll b, ll m, ll n) {
    if(!a) return (b / m) * (n + 1);
    ll ans = 0;
    if(a >= m) {
        ans += (n * (n + 1) / 2) * (a / m); 
        ans += (n + 1) * (b / m);
        ans += f(a % m, b % m, m, n);
    }
    else {
        ll next = (a * n + b) / m;
        ans += n * next;
        ans -= f(m, m - b - 1, a, next - 1);
    }
    return ans;
}
