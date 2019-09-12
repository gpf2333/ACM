#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9 + 100;

unordered_map<int, int>mp;
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
    int T;
    ll n, v;
    int x0, a, b, p;
    scanf("%d", &T);
    while(T--){
        mp.clear();
        scanf("%lld%d%d%d%d", &n, &x0, &a, &b, &p);
        int Q;
        int up1 = 1e3 + 2, up2 = 1e6;
        ll tmp = qpow(a, up1, p);
        int res = 1;
        for(int i = 1; i <= up2; ++i){
            res = res * tmp % p;
            if(!mp.count(res)){ //取最小的,因为会有超过sqrt(p)会可能有重复的
                mp[res] = i * up1;
            }
        }
        ll inv = (b + (ll)(a - 1) * x0 % p) % p;
        inv = qpow(inv, p - 2, p);
        ll invb = qpow(b, p - 2, p);
        scanf("%d", &Q);
        while(Q--){
            scanf("%lld", &v);
            if(!a){
                if(v == x0){
                    puts("0"); continue ;
                }else if(v == b){
                    puts("1"); continue ;
                }else{
                    puts("-1"); continue ;
                }
            }else if(a == 1){
                ll ans = (v - x0 + p) * invb % p;
                if(ans < n){
                    printf("%lld\n", ans); 
                }else{
                    puts("-1");
                }
                continue ;
            }else{
                int ans = INF;
                int d = (v % p * (a - 1 + p) % p + b) % p;
                d = (ll)d * inv % p;
                res = d;
                for(int i = 0; i <= up1; ++i){
                    if(mp.count(res)){
                        ans = min(ans, mp[res] - i);
                    }
                    res = (ll)res * a % p;
                }
                if(ans == INF || ans >= n){
                    puts("-1");
                }else{
                    printf("%d\n", ans);
                }
            }
        }
    }
    return 0;
}