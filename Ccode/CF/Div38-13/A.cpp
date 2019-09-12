#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 205;
int a[maxn];
int b[maxn], c[maxn];

ll gcd(ll a, ll b){
    return !b ? a : gcd(b, a % b);
}

ll qpow(ll a, int b, int mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    // ios::sync_with_stdio(0);
    int n;
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        int pos = 1;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            if(a[i] == 1) pos = i;
        }
        int cntb = 0, cntc = 0;
        for(int i = pos; i <= n; ++i){
            b[++cntb] = a[i];
        }
        for(int i = 1; i < pos; ++i){
            b[++cntb] = a[i];
        }
        for(int i = pos; i >= 1; --i){
            c[++cntc] = a[i];
        }
        for(int i = n; i > pos; --i){
            c[++cntc] = a[i];
        }
        bool ok = 1;
        for(int i = 2; i <= n; ++i){
            if(b[i] - b[i - 1] > 1){
                ok = 0;
            }
        }
        if(ok){
            puts("YES"); continue ;
        }
        ok = 1;
        for(int i = 2; i <= n; ++i){
            if(c[i] - c[i - 1] > 1){
                ok = 0;
            }
        }
        if(ok){
            puts("YES"); continue ;
        }
        else{
            puts("NO"); continue ;
        }
    }    
    return 0;
}