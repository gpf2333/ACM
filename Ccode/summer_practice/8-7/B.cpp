#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 5e4 + 5;
int a[maxn], p[maxn];
int pos[maxn], dp[maxn];
int path[maxn];
int ans[maxn];
bool vis[maxn];

struct Node{
    int val, pos;
}b[maxn];

int main(){
    int T;
    int n;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            dp[i] = INF, vis[i] = 0;
        }
        for(int i = 1; i <= n; ++i){
            scanf("%d", &p[i]);
        }
        dp[1] = a[1];
        int len = 1;
        pos[1]  = len;
        for(int i = 2; i <= n; ++i){
            if(a[i] > dp[len]){
                dp[++len] = a[i];
                pos[i] = len;
            }else{
                int m = lower_bound(dp + 1, dp + len + 1, a[i]) - dp;
                dp[m] = a[i];
                pos[i] = m;
            }
        }
        int mx = INF, c = len;
        for(int i = n; i; --i){
            if(!c) break ;
            if(pos[i] == c && mx > a[i]){
                path[c--] = i;
                vis[i] = 1;
                mx = a[i];
            }
        }
        ans[n] = len;
        for(int i = n - 1; i; --i){
            if(!vis[p[i + 1]]){
                ans[i] = ans[i + 1];
            }else{
                vis[p[i + 1]] = 0;
                int cnt = 0;
                for(int j = 1; j <= ans[i + 1]; ++j){
                    if(vis[path[j]]){
                        b[++cnt].val = a[path[j]];
                        b[cnt].pos = path[j];
                        dp[cnt] = INF;
                    }
                }
                dp[1] = b[1].val, len = 1, pos[i] = len;
                for(int j = 2; j <= cnt; ++j){
                    if(b[j].val > dp[len]){
                        dp[++len] = b[j].val;
                        pos[j] = len;
                    }else{
                        int m = lower_bound(dp + 1, dp + len + 1, b[j].val) - dp;
                        dp[m] = b[j].val;
                        pos[j] = m;
                    }
                }
                int mx = INF, c = len;
                for(int j = cnt; j; --j){
                    if(!c) break ;
                    if(pos[j] == c && mx > b[j].val){
                        path[c--] = b[j].pos;
                        mx = b[j].val;
                    }
                }
                ans[i] = len;
            }
        }
        printf("%d", ans[1]);
        for(int i = 2; i <= n; ++i){
            printf(" %d", ans[i]);
        }
        puts("");
    }
    return 0;
}