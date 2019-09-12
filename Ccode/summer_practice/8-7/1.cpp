#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e3 + 5;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

bool check(ll n, ll k, int m){
    int cnt = 0;
    for(ll i = n + 1; ; ++i){
        if(gcd(i, n) == 1){
            ++cnt;
            if(m == cnt){
                return (((i - n) ^ n) == k);
            }
        }
    }
}

int main(){
    int T, m;
    ll k;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%d", &k, &m);
        ll low = max(1LL, k - maxn);
        ll up = k + maxn;
        //cout << low << " " << up << endl;
        ll ans = -1;
        for(ll i = low; i <= up; ++i){
            if(check(i, k, m)){
                ans = i; break ;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}