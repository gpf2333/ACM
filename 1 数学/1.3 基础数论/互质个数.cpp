
typedef long long ll;
vector<ll>fac;
void calc(ll n){
    fac.clear();
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i ==0){
            fac.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) fac.push_back(n);
}
// 求一个数x与n互质的数的个数 二进制枚举,容斥即可
// 扩展可用二分于求与n互质的第k个数
ll solve(ll x){
    if(x <= 0) return 0;
    int n = fac.size();
    int up = (1 << n);
    ll res = x;
    for(int i = 1; i < up; ++i){
        ll tmp = 1;
        for(int j = 0; j < n; ++j){
            if(i & (1 << j)) tmp *= fac[j];
        }
        if(__builtin_parity(i)) res -= x / tmp;
        else res += x / tmp;
    }
    return res;
}