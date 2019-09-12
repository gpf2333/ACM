#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
const int mx = 1e4 + 5;
int v[mx], w[mx], dp[maxn];
int main(){
    int m, n;
    while(~scanf("%d%d",&m,&n)){
        for(int i = 1; i <= n; ++i){
            scanf("%d%d",&v[i], &w[i]);
        }
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; ++i){
            for(int j = v[i]; j <= m; ++j){
                dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}