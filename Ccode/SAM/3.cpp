#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;

/*
节点从1开始的后缀自动机模板
 */
const int mx = 26; //字符集大小
struct SAM{
    struct Node{
        int len, link;
        int nxt[mx];
    }st[maxn << 1];
    int sz, last;
    int num[maxn << 1]; //num[i]个子串进过节点i
    void init(){
        sz = 1, last = 1;
        st[1].link = st[1].len = 0;
        for(int c = 0; c < mx; ++c) st[sz].nxt[c] = 0; //note!!!
    }
    void add(int c){
        c -= 'a';
        int p;
        int np = ++sz;
        for(int c = 0; c < mx; ++c) st[sz].nxt[c] = 0; // note
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
                for(int c = 0; c < mx; ++c) st[sz].nxt[c] = 0;
                st[nq].len = st[p].len + 1; // note
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
    int tak[maxn], rk[maxn << 1];
    ll count(const char *s){
        memset(tak, 0, sizeof(tak));
        for(int i = 1; i <= sz; ++i){
            ++tak[st[i].len];
        }
        for(int i = 1; i <= sz; ++i){
            tak[i] += tak[i - 1];
        }
        for(int i = 1; i <= sz; ++i){
            rk[tak[st[i].len]--] = i;
        }
        ll ans = 0;
        int u = 1;
        for(int i = 1; s[i]; ++i){
            num[u = st[u].nxt[s[i] - 'a']] = 1;
        }
        for(int i = sz; i; --i){
            int u = rk[i];
            if(st[u].link){
                num[st[u].link] += num[u];
            }
            if(num[u] > 1){
                ans = max(ans, (ll)num[u] * st[u].len);
            }
        }
        return ans;
    }

}sam;

char s[maxn];

int main(){
    while(~scanf("%s", s + 1)){
        sam.init();
        for(int i = 1; s[i]; ++i){
            sam.add(s[i]);
        }
        printf("%lld\n", sam.count(s));
    }
    return 0;
}