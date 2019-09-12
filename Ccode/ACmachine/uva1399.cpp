#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 100;
  
int n, k;
const int mx = 26;
struct Trie{
    int ch[maxn][mx], f[maxn], val[maxn];
    int sz, rt;
    inline int idx(const char c){
        return c - 'A';
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
            if(ch[u][c] == -1){
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
            val[u] |= val[f[u]];
            for(int c = 0; c < n; ++c){
                if(~ch[u][c]){
                    f[ch[u][c]] = ch[f[u]][c];
                    q.push(ch[u][c]);
                }else{
                    ch[u][c] = ch[f[u]][c];
                }
            }
        }
    }
    int dp[maxn], vis[maxn], nxt[maxn];
    int dfs(int u){
        if(vis[u]) return -1;
        if(~dp[u]) return dp[u];
        vis[u] = 1, dp[u] = 0;
        for(int c = n - 1; ~c; --c){
            int v = ch[u][c];
            if(!~v) continue ;
            if(val[v]) continue ;
            int tmp = dfs(v);
            if(!~tmp) return -1; 
            if(dp[u] < tmp + 1){
                dp[u] = tmp + 1, nxt[u] = c;
            }
        }
        vis[u] = 0;
        return dp[u];
    }
    void solve(){
        for(int i = 0; i <= sz; ++i){
            dp[i] = nxt[i] = -1;
            vis[i] = 0; 
        }
        if((!~dfs(rt)) || !dp[0]){
            puts("No");  return ;
        }else{
            for(int u = rt; ~nxt[u]; u = ch[u][nxt[u]]){
                putchar(nxt[u] + 'A');
            }
            puts(""); return ;
        }
    }
}ac;

char s[60];
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &k);
        ac.init();
        for(int i = 0; i < k; ++i){
            scanf("%s", s);
            ac.insert(s);
        }
        ac.build();
        ac.solve();
    }
    return 0;
}

/*
3
2 4
AAA
AB
BA
BB
2 4
AAA
BBB
ABAB
BBAA
3 7
AA
ABA
BAC
BB
BC
CA
CC
*/