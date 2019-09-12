#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long ll;
ll p[maxn];

ll solve(ll n, int m, ll k){
    ll cur = 0, ans = 0;
    for(int i = 1, j = m; j > 0; ){
        ll l = (p[i] - cur - 1LL) / k * k + 1;
        ll r = l + k - 1;
        ll res = 0;
        while(i <= m && p[i] - cur <= r && j){
            ++i, --j, ++res;
        }
        ++ans;
        cur += res;
    }
    return ans;
}

int main(){
    ll n;
    int m;
    ll k;
    while(~scanf("%lld%d%lld",&n,&m,&k)){
        for(int i = 1; i <= m; ++i){
            scanf("%lld", &p[i]);
        }
        printf("%lld\n", solve(n, m, k));
    }
    return 0;
}