#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
int a[maxn], pos[maxn], pre[maxn], nxt[maxn];
int n, k;
int dp[maxn][20];
void init(){
    for(int i = 0; i <= n; ++i) dp[i][0] = i;
    for(int j = 1; (1 << j) <= n; ++j){
        for(int i = 1; i + (1 << j) - 1 <= n; ++i){
            if(a[dp[i][j - 1]] > a[dp[i + (1 << (j - 1))][j - 1]]){
                dp[i][j] = dp[i][j - 1];
            }else{
                dp[i][j] = dp[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int rmq(int l, int r){
    if(l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l + 1);
    return a[dp[l][k]] > a[dp[r - (1 << k) + 1][k]] ? dp[l][k] : dp[r - (1 << k) + 1][k];
}

ll solve(int l, int r){
    if(l > r){
        return 0;
    }
    int t = rmq(l, r);
    ll ans = 0;
    if(t - l < r - t){
        int tmp = min(nxt[t], r + 1);
        for(int i = t; i >= l; --i){
            tmp = min(tmp, nxt[i]);
            if(tmp <= t) break ;
            ans += max(0, tmp - max(t, i - 1 + a[t] - k));
        }
    }else{
        int tmp = max(pre[t], l - 1);
        for(int i = t; i <= r; ++i){
            tmp = max(tmp, pre[i]);
            if(tmp >= t) break ;
            ans += max(0, min(t, i + 1 - a[t] + k) - tmp);
        }
    }
    return ans + solve(l, t - 1) + solve(t + 1, r);
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &k);
        pos[0] = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            pos[i] = 0;
        }
        init();
        for(int i = 1; i <= n; ++i){
            pre[i] = pos[a[i]];
            pos[a[i]] = i;
            pre[i] = max(pre[i], pre[i - 1]);
        }
        for(int i = n; i >= 1; --i){
            pos[i] = n + 1;
        }
        nxt[n + 1] = n + 1;
        for(int i = n; i >= 1; --i){
            nxt[i] = pos[a[i]];
            pos[a[i]] = i;
            nxt[i] = min(nxt[i], nxt[i + 1]);
        }
        printf("%lld\n", solve(1, n));
    }
    return 0;
}