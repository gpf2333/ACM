#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int maxn = 1000 + 5;
const int mx = 4;
struct Trie{
    int ch[maxn][mx], f[maxn], val[maxn];
    int dp[maxn][maxn];
    int sz, rt;
    inline int idx(const char c){
        if(c == 'A') return 0;
        if(c == 'C') return 1;
        if(c == 'T') return 2;
        return 3;
    }
    int newnode(){
        for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
        val[sz] = 0;
        return sz++;
    }
    void init(){
        sz = 0, rt = newnode();
    }
    void insert(const char *s){
        int u = rt;
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            if(!~ch[u][c]){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
        val[u] = 1;
    }
    void build(){
        queue<int>q;
        f[rt] = rt;
        for(int c = 0; c < mx; ++c){
            if(~ch[rt][c]){
                f[ch[rt][c]] = rt;
                q.push(ch[rt][c]);
            }else{
                ch[rt][c] = rt;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(val[f[u]]) val[u] = 1;
            for(int c = 0; c < mx; ++c){
                if(~ch[u][c]){
                    f[ch[u][c]] = ch[f[u]][c];
                    q.push(ch[u][c]);
                }else{
                    ch[u][c] = ch[f[u]][c];
                }
            }
        }
    }
    int solve(const char *s){
        int n = strlen(s);
        for(int i = 0; i <= n; ++i){
            for(int j = 0; j <= sz; ++j){
                dp[i][j] = INF;
            }
        }
        dp[0][0] = 0;
        for(int i = 0; i <= n; ++i){
            for(int j = 0; j < sz; ++j){
                if(dp[i][j] == INF) continue;
                for(int c = 0; c < mx; ++c){
                    if(val[ch[j][c]]) continue ;
                    int t = (idx(s[i]) != c) ? 1 : 0;
                    dp[i + 1][ch[j][c]] = min(dp[i + 1][ch[j][c]], dp[i][j] + t);
                }
            }
        }
        int res = INF;
        for(int i = 0; i < sz; ++i){
            res = min(res, dp[n][i]);
        }
        return (res == INF) ? -1 : res;
    }
}ac;
char s[maxn];
int main(){
    int n, kase = 0;
    while(~scanf("%d", &n)){
        if(n == 0) break ;
        ac.init();
        for(int i = 0; i < n; ++i){
            scanf("%s",s);
            ac.insert(s);
        }
        ac.build();
        scanf("%s",s);
        printf("Case %d: %d\n", ++kase, ac.solve(s));
    }
    return 0;
}