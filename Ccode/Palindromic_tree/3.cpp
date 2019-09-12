#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 300000 + 100;

const int mx = 26;
struct Pailndromic_Tree{
    int ch[maxn][mx], f[maxn], len[maxn], s[maxn];
    int cnt[maxn];
    int num[maxn];
    int last, sz, n;
    int newnode(int x){
        for(int i = 0; i < mx; ++i){
            ch[sz][i] = 0;
        }
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
        for(int i = sz - 1; ~i; --i){
            cnt[f[i]] += cnt[i];
        }
    }
    ll solve(){
        ll ans = 0;
        for(int i = 2; i < sz; ++i){
            ans = max(ans, (ll)len[i] * cnt[i]);
        }
        return ans;
    }
}pam;

char s[maxn];
int main(){
    while(~scanf("%s", s)){
        int len = strlen(s);
        pam.init();
        for(int i = 0; i < len; ++i){
             pam.add(s[i]);
        }
        pam.count();
        printf("%lld\n", pam.solve());
    }
    return 0;
}