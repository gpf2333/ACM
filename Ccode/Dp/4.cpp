#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 5;
int dp[maxn];
int main(){
    int V, n;
    int v[45];
    while(~scanf("%d%d",&V, &n)){
        for(int i = 1; i <= n; ++i){
            scanf("%d",&v[i]);
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int i = 1; i <= n; ++i){
            for(int j = V; j >= v[i]; --j){
                dp[j] |= dp[j - v[i]];
            }
        }
        for(int j = V; j >= 0; --j){
            if(dp[j]){
                printf("%d\n", V - j);
                break ;
            }
        }
    }
    return 0;
}