#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
vector<ll>fac;
ll mul(ll a, ll b, ll mod){
    ll res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll qpow(ll a, ll b, ll mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

//T(n) = slogn(n) s >=5 时候准确率达到99%以上
bool Miller_Rabin(ll n, int s){
    if(n == 2) return 1;
    if(n < 2 || !(n & 1)) return 0;
    int t = 0;
    ll x, y, u = n - 1;
    while((u & 1) == 0){
        ++t;
        u >>= 1;
    }
    for(int i = 0; i < s; ++i){
        ll a = rand() % (n - 1) + 1;
        ll x = qpow(a, u, n);
        for(int j = 0; j < t; ++j){
            ll y = mul(x, x, n);
            if(y == 1 && x != 1 && x != n - 1){
                return 0;
            }
            x = y;
        }
        if(x != 1) return 0;
    }
    return 1;
}

ll gcd(ll a, ll b){
    return b ? gcd(b, a % b): a;
}

ll Pollard_rho(ll n, ll c){
    if(!(n & 1)) return 2;
    ll x = rand() % n;
    ll y = x, i = 1, k = 2;
    while(1){
        ++i;
        x = (mul(x, x, n) + c) % n;
        ll d = gcd(y - x, n);
        if(d > 1 && d < n) return d;
        if(y == x) return n;
        if(i == k) y = x, k += k;
    }
}

void find(ll n){
    if(Miller_Rabin(n, 5)){
        // fac[++fac[0]] = n;
        fac.push_back(n); //可能有重复
        return ;
    }
    ll p = n;
    while(p >= n) p = Pollard_rho(p, (ll)(rand() % (n - 1) + 1));
    find(p), find(n / p);
}

void solve(ll n){
    fac.clear();
    srand(time(NULL));
    find(n);
    if((int)fac.size() == 1){
        puts("Prime");
    }else{
        ll ans = 1e18;
        for(int i = 0; i < (int)fac.size(); ++i){
            ans = min(ans, fac[i]);
        }
        printf("%lld\n", ans);
    }
}

int main(){
    srand(time(NULL));
    int T;
    ll n;
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &n);
        solve(n);
    }
    return 0;
}