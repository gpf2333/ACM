#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
const int mx = 26;
char s[maxn], t[maxn];
int ch[maxn][mx];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s%s", s + 1, t + 1);
    for(int i = 0; i < mx; ++i) ch[n][i] = -1;
    for(int i = n; i >= 1; --i){
        for(int j = 0; j < mx; ++j) ch[i - 1][j] = ch[i][j];
        if(i != n) ch[i - 1][s[i] - 'a'] = i;
    }
    int ans = -1, cur = 0;
    for(int i = 1; i <= m; ++i){
        for(int j = t[i] - 'a' + 1; j < mx; ++j){
            if(ch[cur][j] != -1) ans = max(ans, (i - 1) + n - ch[cur][j] + 1);
        }
        if(ch[cur][t[i] - 'a'] == -1){
            ans = -1; break ;
        }
        cur = ch[cur][t[i] - 'a'];
    }
    printf("%d\n", ans);
    return 0;
}