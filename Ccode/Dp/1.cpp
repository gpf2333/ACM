// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 30000 + 5;
// int dp[26][maxn];
// int v[26], w[26];
// int main(){
//     int n, m;
//     while(~scanf("%d%d",&n,&m)){
//         memset(dp, 0, sizeof(dp));
//         for(int i = 1; i <= m; ++i){
//             scanf("%d%d",&v[i], &w[i]);
//         }
//         for(int i = 1; i <= m; ++i){
//             for(int j = 0; j <= n; ++j){
//                 dp[i][j] = dp[i - 1][j];
//                 if(j > v[i]){
//                     dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i]] + v[i] * w[i]);
//                 }
//             }
//         }
//         printf("%d\n", dp[m][n]);
//     }
//     return 0;
// }

// 01 背包
#include<bits/stdc++.h>
using namespace std;
const int maxn = 30000 + 100;
int dp[maxn];
int main(){
    int v[30], w[30];
    int n, m;
    while(~scanf("%d%d",&m,&n)){
        for(int i = 1; i <= n; ++i){
            scanf("%d%d",&v[i], &w[i]);
            w[i] = v[i] * w[i];
        }
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; ++i){
            for(int j = m; j >= v[i]; --j){
                if(j >= v[i]){
                    dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
                }
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}

/*
常数优化
for(int i=1;i<=n;i++)
{
    sumw+=w[i];
    bound=max(m-sumw,w[i]);
    for(int c=m;c>=bound;c--)
    {
        if(c>=w[i])
        f[c]=max(f[c],f[c-w[i]]+v[i]);
    }
}
 */