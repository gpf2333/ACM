#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

const int mx = 26;
struct PAM{
    int ch[maxn][mx], f[maxn], len[maxn], s[maxn];
    int cnt[maxn];
    int num[maxn];
    int last, sz, n;
    int newnode(int x){
        memset(ch[sz], 0, sizeof(ch[sz]));
        cnt[sz] = num[sz] = 0, len[sz] = x;
        return sz++;
    }
    void init(){
        sz = 0;
        newnode(0), newnode(-1);
        last = n = 0, s[0] = -1, f[0] = 1;
    }
    int get_fail(int u){
        while(s[n - len[u] - 1] != s[n]) u = f[u];
        return u;
    }
    void add(int c){
        c -= 'a';
        s[++n] = c;
        int u = get_fail(last);
        if(!ch[u][c]){
            int np = newnode(len[u] + 2);
            f[np] = ch[get_fail(f[u])][c];
            num[np] = num[f[np]] + 1;
            ch[u][c] = np;
        }
        last = ch[u][c];
        ++cnt[last];
    }
    void count(){
        for(int i = sz - 1; ~i; ++i) cnt[f[i]] += cnt[i];
    }
    bool vis[maxn];
    int down[maxn], up[maxn];
    int tmp[maxn];
    int dfs(int u){
        down[u] = 1, up[u] = 0;
        vector<int>tmp;
        for(int x = u; x > 1 && vis[x] == 0; x = f[x]){
            vis[x] = 1, ++up[u];
            tmp.push_back(x);
        }
        for(int i = 0; i < mx; ++i){
            if(ch[u][i] == 0) continue ;
            down[u] += dfs(ch[u][i]);
        }
        for(int i = 0; i < (int)tmp.size(); ++i){
            vis[tmp[i]] = 0;
        }
        return down[u];
    }
    ll solve(){
        dfs(0), dfs(1);
        ll ans = 0;
        for(int i = 2; i < sz; ++i){
            ans += (1LL * down[i] * up[i] - 1);
        }
        return ans;
    }
}pam;

char s[maxn];
int main(){
    int T, kase = 0;
    scanf("%d", &T);
    while(T--){
        scanf("%s", s);
        pam.init();
        for(int i = 0; s[i]; ++i){
            pam.add(s[i]);
        }
        printf("Case #%d: %lld\n", ++kase, pam.solve());
    }
    return 0;
}