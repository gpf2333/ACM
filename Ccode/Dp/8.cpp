#include<bits/stdc++.h>
using namespace std;
const int maxn = 100 + 50;
const int INF = 0x3f3f3f3f;
char a[maxn], b[maxn];
int dp[maxn][maxn];
int cnta[maxn], cntb[maxn];
int main(){
    int n, m;
    int mp[256];
    memset(mp, 0, sizeof(mp));
    mp['A'] = 0,  mp['C'] = 1, mp['G'] = 2, mp['T'] = 3;
    const int c[5][5] = {
        5, -1, -2, -1, -3,
        -1, 5, -3, -2, -4,
        -2, -3, 5, -2, -2,
        -1, -2, -2, 5, -1,
        -3, -4, -2, -1, 0,
    };
    scanf("%d%s", &n, a);
    scanf("%d%s", &m, b);
    for(int i = 1; i <= n; ++i){
        cnta[i] = mp[a[i - 1]];
    }
    for(int i = 1; i <= m; ++i){
        cntb[i] = mp[b[i - 1]];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    for(int i = 1; i <= n; ++i){
        dp[i][0] = dp[i - 1][0] + c[cnta[i]][4];
    }
    for(int i = 1; i <= m; ++i){
        dp[0][i] = dp[0][i - 1] + c[cntb[i]][4];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + c[cnta[i]][4]);
            dp[i][j] = max(dp[i][j], dp[i][j - 1] + c[4][cntb[j]]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + c[cnta[i]][cntb[j]]);
        }
    }
    printf("%d\n", dp[n][m]);
    return 0;
}
