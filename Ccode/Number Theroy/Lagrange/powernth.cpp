// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const int mod = 1e9 + 10;
// const int maxn = 1e6 + 10;

// int x[maxn], y[maxn];
// int fac[maxn], invf[maxn], pre[maxn], suf[maxn];

// int qpow(int a, int b, int mod){
//     int res = 1;
//     while(b > 0){
//         if(b & 1) res = (ll)res * a % mod;
//         a = a * a % mod;
//         b >>= 1;
//     }
//     return res;
// }

// int lagrange(int n, int x[], int y[], int xi){
//     pre[0] = suf[n + 1] = fac[0] = 1;
//     for(int i = 1; i <= n; ++i) pre[i] = (ll)pre[i - 1] *(n - i) % mod;
//     for(int i = n; i >= 1; --i) suf[i] = (ll)suf[i + 1] * (n - i) % mod;
//     for(int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % mod;
//     invf[n] = qpow(fac[n], mod - 2, mod);
//     for(int i = n - 1; ~i; --i) invf[i] = (ll)invf[i + 1] * (i + 1) % mod;
//     int tmp1, tmp2;
//     for(int i = 1; i <= n; ++i) y[i] = (y[i - 1] + qpow(i, n, mod)) % mod;

// }

// int main(){
//     int n, k;
//     scanf("%d%d", &n, &k);
    
//     return 0;
// }
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define int long long

using namespace std;
const int MAXN = 1000005;
const int MOD = 1e9+7;

int n,k,inv[MAXN],y[MAXN];
int pre[MAXN],suf[MAXN],ans,fac[MAXN];

int fast_pow(int x,int y){
    int ret=1;
    for(;y;y>>=1){
        if(y&1) ret=ret*x%MOD;
        x=x*x%MOD;
    }
    return ret;
}

signed main(){
    scanf("%lld%lld",&n,&k);
    pre[0]=1;for(int i=1;i<=k+2;i++) pre[i]=pre[i-1]*(n-i)%MOD;
    suf[k+3]=1;for(int i=k+2;i;i--) suf[i]=suf[i+1]*(n-i)%MOD;
    fac[0]=1;for(int i=1;i<=k+2;i++) fac[i]=fac[i-1]*i%MOD;
    inv[k+2]=fast_pow(fac[k+2],MOD-2);
    for(int i=k+1;~i;i--) inv[i]=inv[i+1]*(i+1)%MOD;int s1,s2;
    for(int i=1;i<=k+2;i++) y[i]=(y[i-1]+fast_pow(i,k))%MOD;
    for(int i=1;i<=k+2;i++){
        s1=pre[i-1]*suf[i+1]%MOD;
        s2=inv[i-1]*inv[k+2-i]*(((k+2-i)&1)?-1:1)%MOD;
        ans=((ans+s1*s2%MOD*y[i]%MOD)%MOD+MOD)%MOD;
    }
    printf("%lld\n",ans);
    return 0;
}