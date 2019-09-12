#include<bits/stdc++.h>
using namespace std;
const int maxn = 32000;
const int mx = 65;
struct Node{
    int v, p, q;
}a[mx], b[mx][mx];
int num[mx], cnt[mx], v[mx][mx], w[mx][mx];
int dp[maxn];
int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        memset(num, 0, sizeof(num));
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= m; ++i){
            scanf("%d%d%d",&a[i].v, &a[i].p, &a[i].q);
            if(a[i].q){
                b[a[i].q][++num[a[i].q]] = {a[i].v, a[i].p, a[i].q};
            }
        }
        for(int i = 1; i <= m; ++i){
            if(num[i]){
                memset(dp, -1, sizeof(dp));
                dp[0] = 0;
                for(int j = 1; j <= num[i]; ++j){
                    for(int k = n - a[i].v; k >= b[i][j].v; --k){
                        if(~dp[k - b[i][j].v]){
                            dp[k] = max(dp[k], dp[k - b[i][j].v] + b[i][j].v * b[i][j].p);
                        }
                    }
                }
                for(int j = 0; j <= n - a[i].v; ++j){
                    if(~dp[j]){
                        v[i][++cnt[i]] = j + a[i].v;
                        w[i][cnt[i]] = dp[j] + a[i].v * a[i].p;
                    }
                }
            }
            if(!a[i].q){
                v[i][++cnt[i]] = a[i].v;
                w[i][cnt[i]] = a[i].v * a[i].p;
            }
        }
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        for(int i = 1; i <= m; ++i){
            for(int j = n; j >= 0; --j){
                for(int k = 1; k <= cnt[i]; ++k){
                    if(j >= v[i][k]){
                        dp[j] = max(dp[j], dp[j - v[i][k]] + w[i][k]);
                        ans = max(ans, dp[j]);
                    }
                }   
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
