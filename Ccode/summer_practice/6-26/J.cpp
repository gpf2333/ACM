#include<bits/stdc++.h>
using namespace std;
const int maxn = 60000 + 100;
int a[maxn], b[maxn], dp[maxn][21];

int dfs(int i, int j, int k){
    if(i == 0 || j == 0) return (i + j);
    if(abs(a[i] - b[j]) <= k){
        int tmp = a[i] - b[j] + k;
        if(dp[i][tmp]) return dp[i][tmp];
        return dp[i][tmp] = min(dfs(i - 1, j, k), dfs(i, j - 1, k)) + 1;
    }else{
        return dfs(i - 1, j - 1, k) + 1;
    }
}

int main(){
    int n, k ,T;
    scanf("%d",&T);
    while(T--){
        memset(dp, 0, sizeof(dp));
        scanf("%d%d",&n,&k);
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
        }
        for(int i = 1; i <= n; ++i){
            scanf("%d",&b[i]);
        }
        printf("%d\n", dfs(n, n, k));
    }
    return 0;
}