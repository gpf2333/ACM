#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1e5 + 2000;
struct SuffixArray{
    char s[maxn];
    int sa[maxn], t[maxn], t2[maxn], c[maxn], rk[maxn], height[maxn];
    int id[maxn], ans[maxn];
    bool vis[150];

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
            for(int i = 1; i < m; ++i) c[i] += c[i - 1];
            for(int i = n - 1; ~i; --i) sa[--c[x[y[i]]]] = y[i];
           std::swap(x, y);
            p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; ++i){
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
            }
            if(p >= n) break ;
            m = p;
        }
        --n;
        for(int i = 0; i <= n; ++i) rk[sa[i]] = i;
        for(int i = 0, k = 0; i < n; ++i){
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }

    bool check(int n, int x, int len){
        memset(vis, 0, sizeof(vis));
        int cnt = 0, tmp = 0;
        for(int i = 2; i <= len; ++i){
            if(height[i] < x){
                if(cnt > n / 2) ans[++tmp] = sa[i - 1];
                memset(vis, 0, sizeof(vis));
                cnt = 0;
                continue ;
            }
            if(!vis[id[sa[i - 1]]]){
                vis[id[sa[i - 1]]] = 1, ++cnt;
            }
            if(!vis[id[sa[i]]]){
                vis[id[sa[i]]] = 1, ++cnt;
            }
        }
        if(cnt > n / 2){
            ans[++tmp] = sa[n];
        }
        if(tmp){
            ans[0] = tmp;
            return 1;
        }
        return 0;
    }

    void solve(int n, int len){
        memset(ans, 0, sizeof(ans));
        int l = 1, r = 1000, mid;
        bool ok = 0;
        while(l <= r){
            mid = (l + r) >> 1;
            if(check(n, mid, len)){
                ok = 1, l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        if(!ok){
            puts("?");
            return ;
        }else{
            for(int i = 1; i <= ans[0]; ++i){
                for(int j = ans[i]; j < ans[i] + l - 1; ++j){
                    putchar(s[j]);
                }
                puts("");
            }
        }
    }

}sa;

char s[1100];

int main(){
    int n;
    bool flag = 0;
    while(~scanf("%d",&n) && n){
        int len = 0;
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            for(int j = 0; s[j]; ++j){
                sa.s[len] = s[j];
                sa.id[len++] = i;
            }
            sa.s[len] = '#', sa.id[len++] = i;
        }
        sa.s[len] = '\0';
        if(flag){
            puts("");
        }
        flag = 1;
        if(n == 1){
            puts(s);
            continue ;
        }
        sa.build_sa(len, 210);
        sa.solve(n, len);
    }
    return 0;
}
