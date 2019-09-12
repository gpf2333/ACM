typedef long long ll;
ll getphi(ll n){
    ll res = n;
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            res -= res / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) res -= res / n;
    return res;
}