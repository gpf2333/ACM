// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef __int128_t i128;
// const int maxn = 1e3 + 5;
// const int mod = 1e9 + 7;
// i128 h[maxn];
// i128 b[maxn];
// ll a[maxn];

// ll qpow(ll a, ll b){
//     ll res = 1;
//     while(b > 0){
//         if(b & 1) res = res * a;
//         a = a * a;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
//         b >>= 1;
//     }
//     return res;
// }

// void calc(){
//     h[0] = 2, h[1] = 3, h[2] = 6;
//     for(int i = 3; i <= 21; ++i){
//         h[i] = 4LL * h[i - 1] + 17 * h[i - 2] - 12 * h[i - 3] - 16;
//     }
//     for(int i = 1; i <= 20; ++i){
//         b[i] = 3 * h[i + 1] * h[i] + 9 * h[i + 1] * h[i - 1] + 9 * h[i] * h[i] + 27 * h[i] * h[i - 1];
//         b[i] -= (18 * h[i + 1] - 126 * h[i] - 81 * h[i - 1]);
//         b[i] += 192;
//     }
//     // for(int i = 1; i <= 10; ++i){
//     //     cout << b[i] << " ";
//     // }
//     // cout << endl;
//     for(int i = 1; i <= 10; ++i){
//         a[i] = b[i] + qpow(4, i);
//         a[i] = floor(sqrt((double)a[i]));
//     }
//     for(int i = 1; i <= 10; ++i){
//         cout << a[i] << " " << endl;
//     }
// }
// int main(){
//     calc();
//     return 0;
// }

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