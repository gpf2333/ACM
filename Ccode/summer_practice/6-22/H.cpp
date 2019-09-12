#include<bits/stdc++.h>
using namespace std;
typedef  long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e7 + 100;
int cntp, prime[maxn], mu[maxn];
bool isprime[maxn];
void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    cntp = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                break ;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

ll fast_mul(ll a, ll b){
    ll res = 0;
    while(b > 0){
        if(b & 1){
            res = (res + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll fast_pow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1)   res = fast_mul(res, a) % mod;
        a = fast_mul(a, a) % mod;
        b >>= 1;
    }
    return res % mod;
}


int get(ll n, ll k){
    ll up = fast_pow(n, k);
    ll res = 0;
    //cout << endl;
    for(ll i = 1; i <= up; ++i){
        ll tmp = floor(sqrt(up * 1.0 / i));
        //cout << mu[i] * mu[i] << " " << tmp << " ";
        res += mu[i] * mu[i] * tmp;
    }
    //cout << endl;
    return res;
}

int main(){
    // init();
    // for(int i = 1; i <= 7; ++i){
    //     for(int j = 1; j <= 7; ++j){
    //         printf("%d ", get(i, j));
    //     }
    //     puts("");
    // }
    ll n, k;
    int kase = 0;;
    while(~scanf("%lld%lld",&n, &k)){
        printf("Case #%d: %lld\n", ++kase, fast_pow(n, k));
        //cout << fast_pow(n, k) << endl;
    }
    return 0;
}