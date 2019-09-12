#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T>
void read(T &x){
    x = 0;
    char c = getchar();
    int p = 0;
    for(; c < '0' || c > '9'; c = getchar()) if(c == '-') p = 1;
    for(; c >= '0' && c <= '9'; c= getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    if(p) x = -x; 
}

ll fast_mul(ll a, ll b, ll p){
    ll res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

ll fast_pow(ll a, ll b, ll p){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = fast_mul(res, a, p);
        a = fast_mul(a, a, p);
        b >>= 1;
    }
    return res;
}

map<ll, int>mp1, mp2;
int main(){
    ll x, p;
    int T, n;
    read(T);
    while(T--){
        read(n);
        read(p);
        mp1.clear();
        mp2.clear();
        for(int i = 0; i < n; ++i){
            read(x);
            if(!x) continue ;
            ++mp1[fast_mul(fast_mul(x, x, p), x, p)];
            ++mp2[x];
        }
        ll ans = 0;
        int tmp;
        for(auto it = mp1.begin(); it != mp1.end(); ++it){
            tmp = it->second;
            ans = (ans + (ll)tmp * (tmp - 1) / 2);
        }
        if(p != 3){
            for(auto it = mp2.begin(); it != mp2.end(); ++it){
                tmp = it->second;
                ans = (ans - (ll)tmp * (tmp - 1) / 2);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}