#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<map>
// #include<unordered_map>
#include<math.h>
using namespace std;
typedef long long ll;

// unordered_map<int, int>mp;
map<ll, int>mp;
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
    int p, a, b;
    while(~scanf("%d%d%d", &p, &a, &b)){
        mp.clear();
        if(a % p == 0){
            puts("no solution");
            continue ;
        }
        int m = ceil(sqrt(p));
        ll t = b % p;
        mp[t] = 0;
        for(int j = 1; j <= m; ++j){
            t = t * a % p;
            mp[t] = j;
        }
        t = qpow(a, m, p);
        ll res = 1;
        bool ok = 1;
        for(int i = 1; i <= m; ++i){
            res = res * t % p;
            if(mp[res]){
                ok = 0;
                int ans = i * m - mp[res];
                printf("%d\n", ans);
                break ;
            }
        }
        if(ok){
            puts("no solution");
        }
    }
}