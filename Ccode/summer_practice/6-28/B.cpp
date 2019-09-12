#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 2500 + 5;
const int mx = 2;
int dp[2][maxn][(1 << 6) + 10];
struct Trie{
    int ch[maxn][2], f[maxn], val[maxn], tag[maxn];
    int sz, rt;
    inline int idx(const char c){
        return c - '0';
    }
    int newnode(){
        for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
        val[sz] = tag[sz] = 0;
        return sz++;
    }
    void init(){
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        sz = 0; rt = newnode();
    }
    void insert(const char *s, int id, int flag){
        int u = rt;
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            if(!~ch[u][c]){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
        if(!flag){
            val[u] |= (1 << id);
        }else{
            tag[u] |= (1 << id);
        }
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
            tag[u] |= tag[f[u]];
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
    int solve(int n, int L){
        int up = (1 << n), cur = 0, nex = 1;
        dp[0][0][0] = 1;
        for(int i = 0; i < L; ++i){
            nex = cur ^ 1;
            for(int j = 0; j < sz; ++j){
                for(int k = 0; k < up; ++k){
                    dp[nex][j][k] = 0;
                }
            }
            for(int j = 0; j < sz; ++j){
                for(int k = 0; k < up; ++k){
                    if(!dp[cur][j][k]) continue ;
                    for(int c = 0; c < mx; ++c){
                        int cc = ch[j][c], sta = k | val[cc];
                        if(i == L - 1){
                            sta |= tag[cc];
                        }
                        dp[nex][cc][sta] = (dp[nex][cc][sta] + dp[cur][j][k]) % mod;
                    }
                }
            }
            cur = cur ^ 1;
        }
        int res = 0;
        for(int i = 0; i < sz; ++i){
            res = (res + dp[cur][i][up - 1]) % mod;
        }
        return res % mod;
    }
}ac;
char s[maxn];
char rs[maxn];
int main(){
    int T, n, L;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&L);
        ac.init();
        for(int i = 0; i < n; ++i){
            scanf("%s",s);
            ac.insert(s, i, 0);
            int len = strlen(s), rlen = 0;
            for(int j = 0; s[j]; ++j){
                rs[rlen++] = (s[len - j - 1] == '0') ? '1' : '0';
            }
            rs[rlen] = '\0';
            ac.insert(rs, i, 0);
            for(int j = 0; j < len - 1; ++j){
                string s1 = "", s2 = "";
                for (int k = j; k >= 0; k--) s1 += s[k];
                for (int k = j + 1; k < len; k++) s2 += s[k];
                bool flag = true;
                for (int k = 0; k < (int)s1.length() && k < (int)s2.length(); k++) {
                    if (s1[k] == s2[k]) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) continue;
                reverse(s1.begin(), s1.end());
                for (int k = (j + 1) * 2; k < len; k++) {
                    s1 = (s[k] == '0' ? '1' : '0') + s1; // note
                }
                strcpy(rs, s1.c_str());
                ac.insert(rs, i, 1);
            }
        }
        ac.build();
        printf("%d\n", ac.solve(n, L));
    }
    return 0;
}
