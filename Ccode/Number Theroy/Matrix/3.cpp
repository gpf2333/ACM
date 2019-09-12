#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod, phi;
bool flag;
const int N = 2;
struct mat{
    ll v[N][N];
    mat(){ std::memset(v, 0, sizeof(v)); }
    void clear(){std::memset(v, 0, sizeof(v));}
    void init(){ for(int i = 0; i < N; ++i) v[i][i] = 1;}
    ll * operator[](int x){ return v[x];}
    const ll * operator[](int x)const { return v[x];}
    mat operator * (const mat&b){
        const mat&a = *this;
        mat c;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                for(int k = 0; k < N; ++k){
                    if(flag){ 
                        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
                    }
                    else{
                        c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
                        if(c[i][j] >= phi){
                            c[i][j] = c[i][j] % phi + phi;
                        }
                    }
                    
                }
            }
        }
        return c;
    }
    mat qpow(ll b) const{
        mat a = *this, res;
        res.init();
        while(b > 0){
            if(b & 1)  res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
};

int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    mat A;
    A[0][0] = 1, A[0][1] = 1;
    A[1][0] = 1, A[1][1] = 0;
    int T,n, a, b, p;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d%d",&a, &b, &n, &p);
        ll tmp1 = qpow(a, (p - 1) >> 1, p);
        ll tmp2 = qpow(b, (p - 1) >> 1, p);
        if(tmp1 + 1 == p || tmp2 + 1 == p){
            puts("0"); continue ;
        }
        mod = p, phi = p - 1;
        flag = 0;   
        mat res = A.qpow(n - 1);
        ll m = (res[0][0] + res[0][1]);
        if(m >= phi) m = m % phi + phi;
        mat B;
        B[0][0] = 2LL * ((ll)a + b) % p;
        B[0][1] = (-(ll)(a - b) * (a - b) % p + p) % p;
        B[1][0] = 1, B[1][1] = 0;
        flag = 1;
        res = B.qpow(m - 1);
        ll c1 = 2LL * ((ll)a + b) % p;
        ll c2 = 2LL;
        ll ans = (res[0][0] * c1 % mod + res[0][1] * c2 % mod) % mod;
        ans = 4LL * ans % mod;
        printf("%lld\n", ans);
    }
    return 0;
}