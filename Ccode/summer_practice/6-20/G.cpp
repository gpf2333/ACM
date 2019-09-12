#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int m, p;

ll fast_pow(ll a, ll b, ll p){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll getphi(int n){
    ll ans = n;
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            ans = ans / i * (i - 1);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}

ll get(int d, int n){
    return (ll)d * d % mod * (((ll)n * getphi(n) + (n == 1)) / 2) % mod; // note (n == 1)
}

int main(){
    ll inv2 = fast_pow(2, mod - 2, mod);
    int T, m, p, kase = 0;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&m, &p);
        int n = p - 1;
        ll sum = 0;
        for(int i = 1; (ll)i * i <= n; ++i){
            if(n % i == 0){
                sum = (sum + get(i, n / i)) % mod;
                if(i * i == n){
                    continue ;
                }else{
                    sum = (sum + get(n / i, i)) % mod;
                }
            }
        }
        sum = ((sum - ((ll)n * (ll)(n + 1) % mod * inv2 % mod))  + mod )% mod ;
        sum = ((ll)m * sum) % mod;
        printf("Case #%d: %lld\n", ++kase, sum);
    }
    return 0;
}