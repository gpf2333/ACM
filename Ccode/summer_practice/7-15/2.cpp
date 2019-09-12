#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000 + 100;
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
        --n;
        for(int i = 0; i <= n; ++i) rk[sa[i]] = i;
        for(int i = 0, k = 0; i < n; ++i){
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }

    ll solve(int n){
        ll res = 0;
        for(int i = 1; i <= n; ++i){
            res += (n - sa[i] - height[i]);
        }
        return res;
    }

}sa;

int main(){
    int n;
    while(~scanf("%s", sa.s)){
        scanf("%d", &n);
        int len = strlen(sa.s);
        bool ok = 0;
        char c = sa.s[0];
        for(int i = 1; i < len; ++i){
            if(c != sa.s[i]){
                ok = 1; break ;
            }
        }
        if(!ok || len == 1){
            printf("%d\n", n);
            continue ;
        }
        ll ans = (ll)len * (2LL * n - len + 1) / 2LL; 
        sa.build_sa(len, 256);
        ll tmp = sa.solve(len);
        ll cnt = (ll)len * (len + 1) / 2LL - tmp;
        ans -= cnt;
        printf("%lld\n", ans);
    }
    return 0;
}