#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
bool isprime[maxn];
int prime[maxn], cntp;

ll mul(ll a, ll b, ll mod){
    ll res = 0;
    while(b){
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

void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    for(int i = 1; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0) break ;
        }
    }
}

ll getphi(ll n){
    ll ans = n;
    for(int i = 2; (ll)i * i <= n; ++i){
        if(!(n % i)){
            ans = ans / i * (i - 1);
            while(!(n % i))  n /= i;
        }
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}

int main(){
    init();
    int T, p, n, m;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d", &p, &n, &m);
        if(p == 2 || p == 5){
            puts("0"); 
            continue ;
        }
        ll x = 1e18, y = 9LL * p;
        ll phi = getphi(y);
        for(int i = 1; (ll)i * i <= phi; ++i){
            if(phi % i == 0){
                ll tmp = phi / i;
                if(qpow(10, i, y) == 1) x = min(x, (ll)i);
                if(qpow(10, tmp, y) == 1) x = min(x, tmp);
            }
        }
        vector<pair<int, int> >vec;
        ll z = x;
        for(int i = 1; i <= cntp && prime[i] <= z; ++i){
            if(z % prime[i] == 0){
                int c = 0;
                while(z % prime[i] == 0){
                    z /= prime[i];
                    ++c;
                }
                vec.emplace_back(prime[i], c);
            }
        }
        if(z > 1){
            vec.emplace_back(z, 1);
        }
        int up = min(31, m);
        ll ans = 0, g = 1;
        for(int j = 1; j <= up; ++j){
            g = 1;
            for(auto &v: vec){
                g *= qpow(v.first, ceil(1.0 * v.second / j), 1e10);
            }
            ans += n / g;
        }
        if(m > 31){
            ans += (ll)(n / g) * (m - 31);
        }
        printf("%lld\n", ans);
    }
    return 0;
}