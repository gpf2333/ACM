#include<bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
const int mx = 26;
const int mod = 20090717;
struct Trie{
   int ch[maxn][mx], f[maxn], val[maxn];
   int sz, rt; 
   int dp[27][maxn][1 << 10];
   inline int idx(const char c){
       return c - 'a';
   }
   int newnode(){
       for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
       val[sz] = 0;
       return sz++;
   }
   void init(){
       memset(dp, 0, sizeof(dp));
       dp[0][0][0] = 1; //note!!!
       sz = 0, rt = newnode();
   }
   void insert(const char *s, const int id){
       int u = rt;
       for(int i = 0; s[i]; ++i){
           int c = idx(s[i]);
           if(!~ch[u][c]){
               ch[u][c] = newnode();
           }
           u = ch[u][c];
       }
       val[u] |= (1 << id); 
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
    int getnum(int n){
        int cnt = 0;
        while(n){
            if(n & 1) ++cnt;
            n >>= 1;
        }
        return cnt;
    }
    int solve(int n, int m, int up){
        int res = 0, upp = (1 << m);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < sz; ++j){
                for(int k = 0; k < upp; ++k){
                    if(!dp[i][j][k]) continue ;
                    for(int c = 0; c < mx; ++c){
                        int cc = ch[j][c];
                        dp[i + 1][cc][k | val[cc]] = (dp[i + 1][cc][k | val[cc]] + dp[i][j][k]) % mod;
                    }
                }
            }
        }
        for(int i = 0; i < sz; ++i){
            for(int j = 0; j < upp; ++j){
                if(dp[n][i][j] && getnum(j) >= up){
                    res = (res + dp[n][i][j]) % mod;
                }
            }
        }
        return res;
    }
}ac;
char s[maxn];
int main(){
    int n, m, k;
    while(~scanf("%d%d%d",&n,&m,&k)){
        if(n == 0 && m == 0 && k == 0) break;
        ac.init();
        for(int i = 0; i < m; ++i){
            scanf("%s", s);
            ac.insert(s, i);
        }
        ac.build();
        printf("%d\n", ac.solve(n, m, k));
    }
    return 0;
}