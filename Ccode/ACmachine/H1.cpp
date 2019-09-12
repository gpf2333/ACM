#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000003;
const int maxn = 1000 + 5;
const int mx = 31;
map<char, int>mp;
void pre(){
    mp.clear();
    for(char c = 'a'; c <= 'z'; ++c){
        mp[c] = c - 'a';
    } 
    for(char c = 'A'; c <= 'Z'; ++c){
        mp[c] = c - 'A';
    }
    int cnt = 25;
    for(char c = '0'; c <= '9'; ++c){
        if(c == '0') mp[c] = mp['o'];
        else if(c == '1') mp[c] = mp['i'];
        else if(c == '3') mp[c] = mp['e'];
        else if(c == '5') mp[c] = mp['s'];
        else if(c == '7') mp[c] = mp['t'];
        else{
            mp[c] = ++cnt;
        }
    }
}

struct Trie{
    int ch[maxn][mx], f[maxn], val[maxn];
    int dp[22][maxn][8];
    int sz, rt;
    inline int idx(const char c){
        return mp[c];
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
    int solve(int A, int B){
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        for(int i = 0; i < B; ++i){
            for(int j = 0; j < sz; ++j){
                if(val[j]) continue ;
                for(int st = 0; st < 8; ++st){
                    if(!dp[i][j][st]) continue;
                    for(int c = 0; c <= 25; ++c){
                        int nex = ch[j][c];
                        if(val[nex]) continue ;
                        dp[i + 1][nex][st | 1] = ((ll)dp[i + 1][nex][st | 1] + (ll)dp[i][j][st]) % mod;
                        dp[i + 1][nex][st | 2] = ((ll)dp[i + 1][nex][st | 2] + (ll)dp[i][j][st]) % mod;
                    }
                    for(char c = '0'; c <= '9'; ++c){
                        int nex = ch[j][idx(c)];
                        if(val[nex]) continue ;
                        dp[i + 1][nex][st | 4] = ((ll)dp[i + 1][nex][st | 4] + (ll)dp[i][j][st]) % mod;
                    }
                }
            }
        }
        int res = 0;
        for(int i = A; i <= B; ++i){
            for(int j = 0; j < sz; ++j){
                res = ((ll)res + (ll)dp[i][j][7]) % mod;
            }
        }
        return res;
    }
}ac;
char s[30];
int main(){
    pre();
    int A, B, n;
    while(~scanf("%d%d",&A,&B)){
        ac.init();
        scanf("%d",&n);
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            ac.insert(s);
        }
        ac.build();
        printf("%d\n", ac.solve(A, B));
    }   
}