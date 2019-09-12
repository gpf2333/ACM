#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e5 + 10;

const int mx = 27;
struct SAM{
    struct Node{
        int len, link;
        int nxt[mx];
    }st[maxn << 1];
    int sz, last;
    void init(){
        sz = 1, last = 1;
        st[1].link = st[1].len = 0;
        for(int i = 0; i < mx; ++i) st[sz].nxt[i]  = 0;
    }
    void add(int c){
        c -= 'a';
        int p;
        int np = ++sz;
        for(int i = 0; i < mx; ++i) st[sz].nxt[i]  = 0;
        st[np].len = st[last].len + 1;
        for(p = last; p && !st[p].nxt[c]; p = st[p].link){
            st[p].nxt[c] = np;        
        }
        if(!p){
            st[np].link = 1;
        }else{
            int q = st[p].nxt[c];
            if(st[q].len == st[p].len + 1){
                st[np].link = q;
            }else{
                int nq = ++sz;
                for(int i = 0; i < mx; ++i) st[sz].nxt[i]  = 0;
                st[nq].len = st[p].len + 1;
                for(int i = 0; i < mx; ++i){
                    st[nq].nxt[i] = st[q].nxt[i];
                }
                for(; p && st[p].nxt[c] == q; p = st[p].link){
                    st[p].nxt[c] = nq;
                }
                st[nq].link = st[q].link;
                st[q].link = st[np].link = nq;
            }
        }  
        last = np;
    }
    ll calc(){ //求不同子串数量
        ll ans = 0;
        for(int i = 2; i <= sz; ++i){
            ans += st[i].len - st[st[i].link].len; //状态子串数量等于len[i]-len[link[i]]
        }
        return ans;
    }
}sam;

struct PAM{
    int ch[maxn][26], f[maxn], len[maxn], s[maxn];
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
}pam;

char s[maxn];
int main(){
    while(~scanf("%s", s)){
        pam.init();
        for(int i = 0; s[i]; ++i){
            pam.add(s[i]);
        }
        sam.init();
        for(int i = 0; s[i]; ++i){
            sam.add(s[i]);
        }
        sam.add('z' + 1);
        int len = strlen(s);
        for(int i = len - 1; i >= 0; --i){
            sam.add(s[i]);
        }
        ll ans = sam.calc();
        ans -= (ll)(len + 1) * (len + 1);
        ans += (pam.sz - 2);
        ans /= 2;
        printf("%lld\n", ans);
    }
    return 0;
}
