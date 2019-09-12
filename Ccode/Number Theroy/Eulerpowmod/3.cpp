#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//note Euler Powmod
#define Mod(a, b) (a >= b ? a % b + b : a % b) 
const int maxn = 500000 + 10;

const int N = 2e7 + 5;
bool isprime[N];
int cntp = 0, prime[N / 10], phi[N];

void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0; cntp = 0;
    phi[1] = 1;
    for(int i = 2; i < N; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < N; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                break ;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}

int n, a[maxn]; //x
ll bit[maxn]; //detla

inline int lowbit(int x){
    return x & (-x);
}

void add(int x, int val){
    while(x <= n) bit[x] += val, x += lowbit(x); 
}

ll query(int x){
 
    ll res = a[x]; //note!!!
    while(x) res += bit[x], x -= lowbit(x);
    return res;
}

ll qpow(ll a, ll b, int mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = Mod(res * a, mod);
        a = Mod(a * a, mod);
        b >>= 1;
    }
    return res;
}

ll solve(int l, int r, int p){
    if(l == r || p == 1){
        return Mod(query(l), p);
    }
    return qpow(Mod(query(l), p), solve(l + 1, r, phi[p]), p);
}

int main(){
    init();
    int m;
    scanf("%d%d", &n, &m);
    bit[0] = 0;
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
        bit[i] = 0;
    }
    int op, l, r, x;
    while(m--){
        scanf("%d%d%d%d", &op, &l, &r, &x);
        if(op == 1){
            add(l, x); add(r + 1, -x);
        }else{
            printf("%lld\n", solve(l, r, x) % x);
        }
    }
    return 0;
}