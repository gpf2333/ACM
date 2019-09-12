#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 10;
const int maxn = 1e3 + 10;
const int mx = 26;
char s[MAXN], t[maxn];
int nxt[MAXN][mx];
int dp[maxn][maxn];
int n, m;
 
void init(){
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 0; i <= m; ++i) dp[i][0] = 0;
    for(int i = 0; i < mx; ++i) nxt[n + 1][i] = -1;
    for(int i = n + 1; i; --i){
        for(int j = 0; j < mx; ++j) nxt[i - 1][j] = nxt[i][j];
        if(i != n + 1) nxt[i - 1][s[i] - 'a'] = i;
    }
}
 
int main(){
    scanf("%d%d%s%s", &n, &m, s + 1, t + 1);
    init();
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= i; ++j){
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            if(dp[i - 1][j - 1] == INF) continue ;
            int c = t[i] - 'a';
            if(nxt[dp[i - 1][j - 1]][c] == -1) continue ;
            dp[i][j] = min(dp[i][j], nxt[dp[i - 1][j - 1]][c]);
        }
    }
    int ans = 0;
    for(int i = 0; i <= m; ++i){
        for(int j = 0; j <= m; ++j){
            if(dp[i][j] != INF) ans = max(ans, j);
        }
    }
    printf("%d\n", ans);
    return 0;
}