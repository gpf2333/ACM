// #include<iostream>
// #include<cmath>
// #include<algorithm>
// #include<queue>
// #include<cstring>
// #include<cstdio>
// #include<map>
// using namespace std;
// typedef long long ll;
// const int maxn = 2e5 + 10;
// struct SuffixArray{
//     char s[maxn];
//     int sa[maxn], rk[maxn], tp[maxn],c[maxn],height[maxn];

//     void radixsort(int n, int m)
//     {
//         for(int i = 0; i<= m; ++i) c[i] = 0;
//         for(int i = 1; i <= n; ++i) ++c[rk[i]];
//         for(int i = 1; i <= m; ++i) c[i] += c[i - 1];
//         for(int i = n; i >= 1; --i) sa[c[rk[tp[i]]]--] = tp[i];
//     }

//     void build_sa(int n, int m){
//         for(int i = 1; i <= n; ++i){
//             rk[i] = s[i], tp[i] = i;
//         }
//         radixsort(n, m);
//         for(int k = 1; k <= n; k <<= 1){
//             int p = 0;
//             for(int i = n - k + 1; i <= n; ++i) tp[++p] = i;
//             for(int i = 1; i <= n; ++i){
//                 if(sa[i] > k) tp[++p] = sa[i]-k;
//             }
//             radixsort(n, m);
//             std::swap(rk, tp);
//             p = rk[sa[1]] = 1;
//             for(int i = 2; i <= n; ++i){
//                 rk[sa[i]] = (tp [sa[i]] == tp[sa[i - 1]] && tp[sa[i] + k] == tp[sa[i - 1]+k]) ? p : ++p;
//             }
//             if(p >= n) break;
//             m = p;
//         }
//         int k = 0;
//         for(int i = 1; i <= n; ++i)
//         {
//             if(k) --k;
//             int j = sa[rk[i] - 1];
//             while(i + k <= n && j +k <= n && s[i + k] == s[j + k]) ++k;
//             height[rk[i]] = k;
//         }
//     }
// }sa;
// char s[maxn];
// int main(){
//     while(~scanf("%s",s)){
//         int n = strlen(s);
//         int len = 1;
//         for(int i = 0; s[i]; ++i){
//             sa.s[len++] = s[i];
//         }
//         sa.s[len++] = 'z' + 1;
//         scanf("%s", s);
//         for(int i = 0; s[i]; ++i){
//             sa.s[len++] = s[i];
//         }
//         sa.s[len] = '\0';
//         sa.build_sa(len, 124);
//         int ans = 0;
//         for(int i = 2; i <= len; ++i){
//             if((sa.sa[i - 1] <= n && sa.sa[i] > n) || (sa.sa[i - 1] > n && sa.sa[i] <= n)){
//                 ans = max(ans, sa.height[i]);
//             }
//         }
//         printf("%d\n", ans);
//     }
//     return 0;
// }

#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int maxn = 2e5 + 100;
struct SuffixArray{
    int s[maxn];
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
        int k = 0;
        for(int i = 0; i <= n; ++i) rk[sa[i]] = i;
        for(int i = 0; i < n; ++i){
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }

    bool check(int x, int n){
        int maxx = sa[0], minn = sa[0];
        for(int i = 1; i <= n; ++i){
            if(height[i] < x) maxx = minn = sa[i];
            else{
                if(sa[i] < minn) minn = sa[i];
                if(sa[i] > maxx) maxx = sa[i];
                if(maxx - minn > x) return 1;
            }
        }
        return 0;
    }

    int solve(int n){
        int l = 0, r = n, mid, ans = 0;
        while(l < r){
            mid = (l + r) >> 1;
            if(check(mid, n)){
                ans = mid;
                l = mid + 1;
            }else{
                r = mid;
            }
        }
        return ans < 4 ? 0 : (ans + 1);
    }
}sa;

int main(){
    int n;
    while(~scanf("%d",&n) && n){
        if(n < 10){
            puts("0");
            continue ;
        }
        for(int i = 0; i < n; ++i){
            scanf("%d", &sa.s[i]);
        }
        for(int i = 0; i < n - 1; ++i){
            sa.s[i] = sa.s[i + 1] - sa.s[i] + 90;
        }
        sa.build_sa(n - 1, 190);
        printf("%d\n", sa.solve(n - 1));
    }
    return 0;
}
