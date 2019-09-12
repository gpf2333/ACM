#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 500000 + 100;

int x[maxn], a[maxn], p[maxn], q[maxn];
int dp[maxn], sum[maxn];

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
    scanf("%d", &T);
    while(T--){
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i){
            int r, s;
            scanf("%d%d%d%d", &r, &s, &x[i], &a[i]);
            ll invs = qpow(s, mod - 2, mod);
            p[i] = (ll)r * invs % mod;
            q[i] = (ll)(s - r) * invs % mod;
        }
        dp[0] = dp[1] = 0;
        sum[0] = 0;
        int up = n + 1;
        for(int i = 1; i <= up; ++i){
            ll tmp = ((sum[i - 1] - sum[x[i] - 1]) % mod + mod) % mod;
            dp[i] = (q[i] * tmp % mod + a[i]) % mod;
            dp[i] = dp[i] * qpow(p[i], mod - 2, mod) % mod;
            sum[i] = (sum[i - 1] + dp[i]) % mod;
        }
        // sum[n + 1] = (sum[n] + dp[n + 1]) % mod;
        // for(int i = 1; i <= n + 1; ++i){
        //     cout << dp[i] << " " << sum[i] << endl;
        // }
        while(m--){
            int l, r;
            scanf("%d%d", &l, &r);
            --l, --r;
            int ans = ((sum[r] - sum[l]) % mod + mod) % mod;
            printf("%d\n", ans);
        }
    }
    return 0;
}