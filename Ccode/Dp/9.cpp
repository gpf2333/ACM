// 背包转换
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
int dp[maxn][maxn * 6]; 
bool vis[maxn][maxn * 6];
int v[maxn], w[maxn]; //vis[i][j] 前i件物品是否可以装到体积j
int main(){
    int n, a, b;
    while(~scanf("%d",&n)){
        int sum = 0, ans = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%d%d",&a, &b);
            if(a > b){
                v[i] = 2 * (a - b); //改变的点数之差就是体积
                w[i] = 1;
                sum +=  (a - b);
            }else if(a < b){
                v[i] = 2 * (b - a); 
                w[i] = -1;
                sum += (b - a);
                ++ans;
            }else{
                v[i] = w[i] = 0;
            }
        }
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= sum; ++j){
                dp[i][j] = dp[i - 1][j];
                vis[i][j] = vis[i - 1][j];
                if(j - v[i] == 0 || (j > v[i] && vis[i - 1][j - v[i]])){
                    if(!vis[i][j]){
                        dp[i][j] = dp[i - 1][j - v[i]] + w[i];
                        vis[i][j] = 1;
                    }else{
                        dp[i][j] = min(dp[i][j], dp[i - 1][j - v[i]] + w[i]);
                    }
                }
            }
        }
        for(int j = sum; j; --j){
            if(vis[n][j]){
                ans += dp[n][j]; break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}