#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
const int mx = 26;
struct Trie{
    int ch[maxn][mx];
    int sz, rt;
    inline int idx(const char c){
        return c - 'a';
    }
    int newnode(){
        for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
        return sz++;
    }
    void init(){
        sz = 0, rt = newnode();
    }
    void insert(const char *s, const int len){
        int u = rt;
        for(int i = 0; i < len; ++i){
            int c = idx(s[i]);
            if(ch[u][c] == -1){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
    }
    int query(const char *s , const int len){
        int u = rt, res = 0;
        for(int i = 0; i < len; ++i){
            int c = idx(s[i]);
            if(ch[u][c] == -1) return res;
            ++res;
            u = ch[u][c];
        }
        return res;
    }
}trie;

struct SuffixArray{
    char s[maxn];
    int sa[maxn], t[maxn], t2[maxn], c[maxn], rk[maxn], height[maxn];
    void build_sa(int n, int m){
        ++n;
        int *x = t, *y = t2;
        for(int i = 0; i < m; ++i) c[i] = 0;
        for(int i = 0; i < n; ++i) ++c[x[i] = s[i]];
        for(int i = 1; i < m; ++i) c[i] += c[i - 1];
        for(int i = n - 1; ~i; --i) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1){
            int p = 0;
            for(int i = n - k; i < n; ++i) y[p++] = i;
            for(int i = 0; i < n; ++i){
                if(sa[i] >= k) y[p++] = sa[i] - k;
            }
            for(int i = 0; i < m; ++i) c[i] = 0;
            for(int i = 0; i < n; ++i) ++c[x[y[i]]];
            for(int i = 0; i < m; ++i) c[i] += c[i - 1];
            for(int i = n - 1; ~i; --i) sa[--c[x[y[i]]]] = y[i];
            std::swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for(int i = 1; i < n; ++i){
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
            }
            if(p >= n) break;
            m = p;
        }
        // --n;
        // int i, j, k = 0;
        // for( i = 0; i <= n; ++i) rk[sa[i]] = i;
        // for (i = 0; i < n;  height[rk[i++]] = k){
        //     for(k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
        // }
        --n;
        for(int i = 0; i <= n; ++i) rk[sa[i]] = i;
        for(int i = 0, k = 0; i < n; ++i){
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }
}sa;

char s[maxn];
int pos[maxn];

int main(){
    int T, n, m, x, y;
    scanf("%d",&T);
    while(T--){
        trie.init();
        scanf("%d", &n);
        int cnt = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%s", s + cnt);
            int len = strlen(s + cnt);
            trie.insert(s + cnt, len);
            pos[i] = cnt;
            cnt += (len + 1);
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&x,&y);
            char *sx = s + pos[x], *sy = s + pos[y];
            int lenx = strlen(sx), leny = strlen(sy);
            int len = 0;
            for(int i = 0; i < lenx; ++i){
                sa.s[len++] = sx[i];
            }
            sa.s[len++] = '$';
            for(int i = 0; i < leny; ++i){
                sa.s[len++] = sy[i];
            }
            sa.s[len] = '\0';
            sa.build_sa(len, 128);
            int ans = 0;
            for(int i = 1; i <= len; ++i){
                if(sa.height[i] <= ans) continue ;
                if(sa.sa[i - 1] < lenx && sa.sa[i] > lenx){
                    ans = max(ans, trie.query(s + pos[x] + sa.sa[i - 1], sa.height[i]));
                }else if(sa.sa[i - 1] > lenx && sa.sa[i] < lenx){
                    ans = max(ans, trie.query(s + pos[x] + sa.sa[i], sa.height[i]));   
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}