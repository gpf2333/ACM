#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;

/*
节点从1开始的后缀自动机模板
t为0则表示不同位置的相同子串算作一个,t为1则表示不同位置的相同子串算作多个
k表示输出字典序第k小的子串。
 */
const int mx = 26; //字符集大小
struct SAM{
    struct Node{
        int len, link;
        int nxt[mx];
    }st[maxn << 1];
    int sz, last;
    int num[maxn << 1]; //num[i]个子串进过节点i
    int siz[maxn << 1]; //siz[i]表示i所代表的Endpos的集合大小，也就是i所对应字符串集合的出现次数
    inline void init(){
        sz = 1, last = 1;
        st[1].link = st[1].len = 0;
        for(int c = 0; c < mx; ++c) st[sz].nxt[c] = 0; //note!!!
    }
    void add(int c){
        c -= 'a';
        int p;
        int np = ++sz;
        for(int c = 0; c < mx; ++c) st[sz].nxt[c] = 0; // note
        siz[np] = 1; // note!!! 
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
    void count(int T){
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

        for(int i = sz; i; --i){
            if(T){
                siz[st[rk[i]].link] += siz[rk[i]]; 
            }else{
                siz[rk[i]] = 1;
            }
        }

        siz[1] = 0;
        for(int i = sz; i; --i){
            num[rk[i]] = siz[rk[i]];
            for(int j = 0; j < mx; ++j){
                if(st[rk[i]].nxt[j]){
                    num[rk[i]] += num[st[rk[i]].nxt[j]];
                }
            }
        }
    }

    void solve(int k){
        if(k > num[1]){
            puts("-1"); return ;
        }
        int cur = 1;
        k -= siz[1];
        num[1] = 0;
        while(k > 0){
            int c = 0;
            while(k > num[st[cur].nxt[c]]){
                k -= num[st[cur].nxt[c]];
                ++c;
            }
            cur = st[cur].nxt[c];
            putchar('a' + c);
            k -= siz[cur];
        }
        puts("");
    }

}sam;

char s[maxn];

int main(){
    int T, k;
    while(~scanf("%s", s + 1)){
        scanf("%d%d", &T, &k);
        sam.init();
        for(int i = 1; s[i]; ++i){
            sam.add(s[i]);
        }
        sam.count(T);
        sam.solve(k);
    }
    return 0;
}