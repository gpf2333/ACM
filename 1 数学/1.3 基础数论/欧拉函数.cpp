
typedef long long ll;
// 1到n中和 n互质的数的个数 单次求 sqrt(n)
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

// 性质: 欧拉函数phi(n) 是数字n的既约剩余系周期
// 延申：与n互质的第k个数
ll CalcK(int n, int k, int a[]){
    int cnt = 0;
    for(int i = 1; i <= n; ++i){
        if(gcd(i, n) == 1){
            a[++cnt] = i;
        }
    }
    ll ans = (ll)(k - 1) / cnt * (ll)n + a[(k - 1) % cnt + 1];
    return ans;
}

