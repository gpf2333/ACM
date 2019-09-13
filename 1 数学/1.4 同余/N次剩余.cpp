#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mul(ll a, ll b, const ll mod){
    ll res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll qpow(ll a, ll b, const ll mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(!b){
        return x = 1, y = 0, a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

vector<ll>fac;
bool g_tset(int g, ll p, const vector<ll> &fac){
    for(auto &v: fac){
        if(qpow(g, (p - 1) / v, p) == 1) return 0;
    }
    return 1;
}

int pri_root(ll p){
    fac.clear();
    ll n = p - 1;
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            fac.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) fac.push_back(n);
    for(int g = 1; ; ++g){
        if(g_tset(g, p, fac)) return g;
    }
}

unordered_map<ll, int>mp;
ll bsgs(ll a, ll b, ll m){
    mp.clear();
    ll s = ceil(sqrt(m + 0.5)), cur = 1; 
    for(int i = 0; i < s; ++i){
        if(!mp.count(cur)) mp[cur] = i;
        cur = (ll)cur * a % m;
    }
    ll v = qpow(a, (m - 1 - s + m) % m, m);
    for(int i = 0; i < s; ++i){
        if(mp.count(b)){
            return (ll)s * i + mp[b];
        }
        b = (ll)b * v % m;
    }
    return -1;
}

vector<ll> n_root(ll a, ll n,  ll p){
    vector<ll> ret;
    if(a == 0){
        ret.push_back(0); 
        return ret;
    }
    ll g = pri_root(p); 
    g %= p; //note 
    ll m = bsgs(g, a, p); // g ^ m = a % p; solve: m
    if(m == -1){
        return ret;
    }
    //solve: g ^ nx = g ^ m % p -> nx = m % (p - 1)
    ll A = n,  B = p - 1, C = m, x, y;
    ll d = exgcd(A, B, x, y);
    if(C % d) return ret;
    x = x * (C / d) % B;
    ll delta = B / d;
    for(int i = 0; i < d; ++i){
        x = ((x + delta) % B + B) % B;
        ret.push_back(qpow(g, x, p));
    }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

int main(){
    int cas = 0;
    ll a, n, p;
    while(~scanf("%lld%lld%lld", &n, &p, &a)){
        vector<ll>ans;
        ans = n_root(a, n, p);
        printf("case%d:\n", ++cas);
        if((int)ans.size() == 0){
            puts("-1");
        }else{
            for(auto v: ans){
                printf("%lld\n", v);
            }
        }
    }
    return 0;
}