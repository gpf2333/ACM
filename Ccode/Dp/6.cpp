// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 200;
// int a[maxn], dp[2][maxn];
// int n;
// int main(){
//     int n;
//     while(~scanf("%d",&n)){
//         for(int i = 0; i < n; ++i){
//             scanf("%d", &a[i]);
//             dp[0][i] = dp[1][i] = 1;
//         }
//         for(int i = 0; i < n; ++i){
//             for(int j = 0; j < i; ++j){
//                 if(a[i] > a[j]){
//                     dp[0][i] = max(dp[0][i], dp[0][j] + 1);
//                 }
//             }
//         }
//         for(int i = n - 1; i >= 0; --i){
//             for(int j = n - 1; j > i; --j){
//                 if(a[i] > a[j]){
//                     dp[1][i] = max(dp[1][i], dp[1][j] + 1);
//                 }
//             }
//         }
//         int ans = 0;
//         for(int i = 0; i < n; ++i){
//             ans = max(ans, dp[0][i] + dp[1][i] - 1);
//         }
//         printf("%d\n", n - ans);
//     }
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
const int maxn = 200 + 5;
const int INF = 0x3f3f3f3f;
int a[maxn], dp[2][maxn], f[maxn];
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i = 0; i < n; ++i){
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= n; ++i){
            f[i] = INF;
        }
        f[0] = a[0];
        dp[0][0] = 1;
        int pos = 0;
        for(int i = 1; i < n; ++i){
            if(a[i] > f[pos]){
                f[++pos] = a[i];
                dp[0][i] = pos + 1;
            }else{
                int tmp = lower_bound(f, f + pos + 1, a[i]) - f;
                dp[0][i] = tmp + 1;
                f[tmp] = a[i];
            }
        }
        for(int i = 1; i <= n; ++i){
            f[i] = INF;
        }
        f[0] = a[n - 1];
        dp[1][n - 1] = 1;
        pos = 0;
        for(int i = n - 2; i >= 0; --i){
            if(a[i] > f[pos]){
                f[++pos] = a[i];
                dp[1][i] = pos + 1;
            }else{
                int tmp = lower_bound(f, f + pos + 1, a[i]) - f;
                dp[1][i] = tmp + 1;
                f[tmp] = a[i];
            }
        }
        int ans = 0;
        for(int i = 0; i < n; ++i){
            ans = max(ans, dp[0][i] + dp[1][i] - 1);
        }
        printf("%d\n", n - ans);
    }
    return 0;
}