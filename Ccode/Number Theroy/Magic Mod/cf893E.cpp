#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 2e3;
const int mod = 1e9 + 7;
int qpow(int a, int b){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}
int fac[maxn], invf[maxn];  
void init(){
    fac[0] = 1;
    for(int i = 1; i < maxn; ++i) fac[i] = (ll)fac[i - 1] * i % mod;
    invf[maxn - 1] = qpow(fac[maxn - 1], mod - 2);
    for(int i = maxn - 2; ~i; --i) invf[i] = (ll)invf[i + 1] * (i + 1) % mod;
}
inline int C(int n, int m){
    return (ll)fac[n] * invf[m] % mod * (ll)invf[n - m] % mod;
}
int main(){
    init();
    int q;
    scanf("%d", &q);
    while(q--){
        int x, y;
        scanf("%d%d", &x, &y);
        int ans = qpow(2, y - 1);
        int n = x;
        for(int i = 2; (ll)i * i <= n; ++i){
            if(n % i == 0){
                int cnt = 0;
                while(n % i == 0){
                    n /= i, ++cnt;
                }
                ans = (ll)ans * C(cnt + y - 1, y - 1) % mod;
            }
        }
        if(n > 1) ans = (ll)ans * y % mod;
        printf("%d\n", ans);
    }
    return 0;
}