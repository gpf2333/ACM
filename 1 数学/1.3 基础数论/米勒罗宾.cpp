
typedef long long ll;
const int maxn = 1e5 + 100;
ll mul(ll a, ll b, ll mod){
    ll res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll qpow(ll a, ll b, ll mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

//T(n) = slogn(n) s >=5 时候准确率达到99%以上
bool Miller_Rabin(ll n, int s){
    if(n == 2) return 1;
    if(n < 2 || !(n & 1)) return 0;
    int t = 0;
    ll x, y, u = n - 1;
    while((u & 1) == 0){
        ++t;
        u >>= 1;
    }
    srand(time(NULL));
    for(int i = 0; i < s; ++i){
        ll a = rand() % (n - 1) + 1;
        ll x = qpow(a, u, n);
        for(int j = 0; j < t; ++j){
            ll y = mul(x, x, n);
            if(y == 1 && x != 1 && x != n - 1){
                return 0;
            }
            x = y;
        }
        if(x != 1) return 0;
    }
    return 1;
}