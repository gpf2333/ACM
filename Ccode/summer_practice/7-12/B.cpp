#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
const int NUM = 3;
int N = 3;
struct mat{
    ll a[NUM][NUM];
    void clear(){
        memset(a,0,sizeof(a));
    }
    void init(){
        memset(a,0,sizeof(a));
        for(int i = 0; i < N; ++i) a[i][i] = 1;
    }
    mat operator * (const mat &b) const{
        mat c;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                c.a[i][j] = 0;
                for(int k = 0; k < N; ++k){
                    c.a[i][j] = (c.a[i][j] +  a[i][k] * b.a[k][j] % mod) % mod; 
                }
            }
        }
        return c;
    }
};

mat fast_pow(mat a,ll b){ 
    mat res;
    res.init();
    while(b > 0){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main(){
    long long f[] = {0, 0, 31, 197, 1255};
    ll g[] = {0, 0, 1255, 197, 31};
    mat a;
    a.clear();
    a.a[0][0] = 4; a.a[0][1] = 17, a.a[0][2] = -12;
    a.a[1][0] = 1;
    a.a[2][1] = 1;
    int T;
    long long n;
    scanf("%d", &T);
    while(T--){
        scanf("%lld",&n);
        if(n <= 4){
            printf("%lld\n", f[n]);
            continue ;
        }
        mat A = fast_pow(a, n - 4);
        ll ans = 0;
        for(int i = 2; i <= 4; ++i){
            ans = (ans + (g[i] * A.a[0][i - 2] % mod + mod) % mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}