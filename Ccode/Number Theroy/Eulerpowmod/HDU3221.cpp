#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;

bool isprime[maxn];
int cntp, prime[maxn], phi[maxn];

void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = cntp = 0;
    phi[1] = 1;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                break ;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}


int mod;
int N = 2;
struct mat{
    ll a[2][2];
    void init(){
        memset(a, 0, sizeof(a));
        for(int i = 0; i < N; ++i) a[i][i] = 1;
    }
    void clear(){
        memset(a, 0, sizeof(a));
    }
    mat operator * (const mat &b) const{
        mat c;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                c.a[i][j] = 0;
                for(int k = 0; k < N; ++k){
                    c.a[i][j] += a[i][k] * b.a[k][j];
                    if(c.a[i][j] >= phi[mod]){
                        c.a[i][j] = c.a[i][j] % phi[mod] + phi[mod];
                    }
                }     
            }
        }
        return c; //note!!!
    }
};

mat qpow(mat a, ll b){
    mat res;
    res.init();
    while(b > 0){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

ll qpow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    init();
    mat A;
    A.a[0][0] = A.a[0][1] = 1;
    A.a[1][0] = 1, A.a[1][1] = 0;
    int T;
    scanf("%d", &T);
    int a, b, n, kase = 0;
    while(T--){
        scanf("%d%d%d%d", &a, &b, &mod, &n);
        printf("Case #%d: ", ++kase);
        if(n == 1){
            ll ans = a % mod;
            printf("%lld\n", ans);
            continue ;
        }else if(n == 2){
            ll ans = b % mod;
            printf("%lld\n", ans);
            continue ;
        }else if(n == 3){
            ll ans = (ll)a * b % mod;
            printf("%lld\n", ans);
            continue ;
        }
        mat tmp = qpow(A, n - 3);
        ll tmp2 = (tmp.a[0][0] + tmp.a[0][1]);
        if(tmp2 >= phi[mod]) tmp2 = tmp2 % phi[mod] + phi[mod];
        tmp = qpow(A, n - 4);
        ll tmp1 = tmp.a[0][0] + tmp.a[0][1];
        if(tmp1 >= phi[mod]) tmp1 = tmp1 % phi[mod] + phi[mod];
        ll ans = qpow(a, tmp1) * qpow(b, tmp2) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}