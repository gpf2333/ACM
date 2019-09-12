// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 1e4 + 5;
// int dp[101][maxn];
// int a[101];
// int main(){
//     int n, m;
//     while(~scanf("%d%d",&n,&m)){
//         memset(dp, 0, sizeof(dp));
//         for(int i = 1; i <= n; ++i){
//             scanf("%d",&a[i]);
//         }
//         for(int i = 1; i <= n; ++i){
//             for(int j = 0; j <= m; ++j){
//                 if(j < a[i]) dp[i][j] = dp[i - 1][j];
//                 else if(j == a[i]) dp[i][j] = dp[i - 1][j] + 1;
//                 else{
//                     dp[i][j] = dp[i - 1][j] + dp[i - 1][j - a[i]];
//                 }
//             }
//         }
//         printf("%d\n", dp[n][m]);
//     }
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 100;
int dp[maxn];
int main(){
    int n, m;
    int a[105];
    while(~scanf("%d%d",&n,&m)){
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int i = 1; i <= n; ++i){
            for(int j = m; j >= a[i]; --j){
                if(j >= a[i]){
                    dp[j] += dp[j - a[i]];
                }
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}

