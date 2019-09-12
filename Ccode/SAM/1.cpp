#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;

const int mx = 26;
struct SAM{
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][mx];
    int num[maxn << 1]; //每个结点所代表的字符串的出现次数
    int sz, rt, last;
    int newnode(int x = 0){
        len[sz] = x, link[sz] = -1;
        for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
        return sz++;
    }
    void init(){
        sz = last = 0, rt = newnode(0);
    }
    void reset(){
        last = 0;
    }
    void add(int c){
        c -= 'a';
        int np = newnode(len[last] + 1);
        int p;
        for(p = last; ~p && ch[p][c] == -1; p = link[p]){
            ch[p][c] = np;
        }
        if(p == -1){
            link[np] = rt;
        }else{
            int q = ch[p][c];
            if(len[p] + 1 == len[q]){
                link[np] = q;
            }else{
                int nq = newnode(len[p] + 1);
                for(int i = 0; i < mx; ++i){
                    ch[nq][i] = ch[q][i];
                }
                // memcpy(ch[nq], ch[q], sizeof(ch[q]));
                link[nq] = link[q], link[q] = link[np] = nq;
                for(; ~p && ch[p][c] == q; p = link[p]){
                    ch[p][c] = nq;
                }
            }
        }
        last = np;
    }
    int topcnt[maxn], topsam[maxn << 1];
    ll build(const char *s){
        memset(topcnt, 0, sizeof(topcnt));
        for(int i = 0; i < sz; ++i){
            ++topcnt[len[i]];
        }
        for(int i = 0; i < maxn - 1; ++i){
            topcnt[i + 1] += topcnt[i];
        }
        for(int i = 0; i < sz; ++i){
            topsam[--topcnt[len[i]]] = i;
        }
        int u = rt;
        for(int i = 0; s[i]; ++i){
            num[u = ch[u][s[i] - 'a']] = 1;
        }
        ll ans = 0;
        for(int i = sz - 1; ~i; --i){
            int u = topsam[i];
            if(~link[u]){
                num[link[u]] += num[u];
            }
            if(num[u] > 1) ans = max(ans, (ll)num[u] * len[u]);
        }
        return ans;
    }
}sam;

char s[maxn];

int main(){
    while(~scanf("%s", s)){
        sam.init();
        for(int i = 0; s[i]; ++i){
            sam.add(s[i]);
        }
        printf("%lld\n", sam.build(s));
    }
    return 0;
}