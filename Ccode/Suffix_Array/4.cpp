// /*
// POJ 3415 后缀数组 + 单调栈维护
// */
// #include<iostream>
// #include<algorithm>
// #include<cmath>
// #include<cstdio>
// #include<cstring>
// #include<string>
// using namespace std;
// typedef long long ll;
// const int maxn = 2e5 + 100;
// int sta[maxn][2];
// struct SuffixArray{
//     char s[maxn];
//     int sa[maxn], rk[maxn], tp[maxn], c[maxn], height[maxn];

//     void radixsort(int n, int m){
//         for(int i = 0; i <= m; ++i) c[i] = 0;
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
//                 if(sa[i] > k) tp[++p] = sa[i] - k;
//             }
//             radixsort(n, m);
//             std::swap(rk, tp);
//             p = rk[sa[1]] = 1;
//             for(int i = 2; i <= n; ++i){
//                 rk[sa[i]] = (tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + k] == tp[sa[i] + k]) ? p : ++p;
//             }
//             if(p >= n) break ;
//             m = p;
//         }
//         for(int i = 1, k = 0; i <= n; ++i){
//             if(k) --k;
//             int j = sa[rk[i] - 1];
//             while(s[i + k] == s[j + k]) ++k;
//             height[rk[i]] = k;
//         }
//     }
//     ll solve(int lena, int n, int k){
//         for(int i = 0; i <= n; ++i){
//             sta[i][0] = sta[i][1] = 0;
//         }
//         ll ans = 0;
//         int top = 0;
//         ll cnt = 0;
//         for(int i = 2; i <= n; ++i){
//             if(height[i] < k){
//                 top = 0, cnt = 0;
//             }else{
//                 int num = 0;
//                 if(sa[i - 1] <= lena){
//                     ++num;
//                     cnt += (height[i] - k + 1);
//                 }
//                 while(top && sta[top][0] >= height[i]){
//                     cnt -= (ll)sta[top][1] * (sta[top][0] - height[i]);
//                     num += sta[top][1];
//                     --top;
//                 }
//                 ++top;
//                 sta[top][0] = height[i], sta[top][1] = num;
//                 if(sa[i] > lena) ans += cnt;
//             }
//         }
//         top = cnt = 0;
//         for(int i = 2; i <= n; ++i){
//             if(height[i] < k){
//                 top = 0, cnt = 0;
//             }else{
//                 int num = 0;
//                 if(sa[i - 1] > lena){
//                     ++num;
//                     cnt += (height[i] - k + 1);
//                 }
//                 while(top && sta[top][0] >= height[i]){
//                     cnt -= (ll)sta[top][1] * (sta[top][0] - height[i]);
//                     num += sta[top][1];
//                     --top;
//                 }
//                 ++top;
//                 sta[top][0] = height[i], sta[top][1] = num;
//                 if(sa[i] <= lena) ans += cnt;
//             }
//         }
//         return ans;
//     }
// }sa;
// char s[maxn];
// int main(){
//     int k;
//     while(~scanf("%d",&k) && k){
//         scanf("%s", s);
//         int lena = strlen(s);
//         int len = 1;
//         for(int i = 0; s[i]; ++i){
//             sa.s[len++] = s[i];
//         }
//         sa.s[len++] = '$';
//         scanf("%s",s);
//         for(int i = 0; s[i]; ++i){
//             sa.s[len++] = s[i];
//         }
//         sa.s[len] = '\0';
//         sa.build_sa(len, 130);
//         printf("%I64d\n", sa.solve(lena, len, k));
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
const int maxn = 2e5 + 100;
int sta[maxn][2];
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
    /*
        把每一个height的值捆绑一个num，原因是再进行更新的时候，
        直接减去栈顶对应的 num *（栈顶对应的height-当前的height）。
     */
    ll solve(int lena, int n, int k){
        for(int i = 0; i <= n; ++i){
            sta[i][0] = sta[i][1] = 0;
        }
        ll ans = 0;
        int top = 0;
        ll cnt = 0;
        for(int i = 1; i <= n; ++i){
            if(height[i] < k){
                top = 0, cnt = 0;
            }else{
                int num = 0;
                if(sa[i - 1] < lena){
                    ++num;
                    cnt += (height[i] - k + 1);
                }
                while(top && sta[top][0] >= height[i]){
                    cnt -= (ll)sta[top][1] * (sta[top][0] - height[i]);
                    num += sta[top][1];
                    --top;
                }
                ++top;
                sta[top][0] = height[i], sta[top][1] = num;
                if(sa[i] > lena) ans += cnt;
            }
        }
        top = cnt = 0;
        for(int i = 1; i <= n; ++i){
            if(height[i] < k){
                top = 0, cnt = 0;
            }else{
                int num = 0;
                if(sa[i - 1] > lena){
                    ++num;
                    cnt += (height[i] - k + 1);
                }
                while(top && sta[top][0] >= height[i]){
                    cnt -= (ll)sta[top][1] * (sta[top][0] - height[i]); //减去多余的贡献
                    num += sta[top][1];
                    --top;
                }
                ++top;
                sta[top][0] = height[i], sta[top][1] = num;
                if(sa[i] < lena) ans += cnt;
            }
        }
        return ans;
    }

}sa;
char s[maxn];
int main(){
    int k;
    while(scanf("%d", &k)){
        if(!k) break ;
        scanf("%s", s);
        int n = strlen(s);
        int len = 0;
        for(int i = 0; s[i]; ++i){
            sa.s[len++] = s[i];
        }
        sa.s[len++] = '$';
        scanf("%s", s);
        for(int i = 0; s[i]; ++i){
            sa.s[len++] = s[i];
        }
        sa.s[len] = '\0';
        sa.build_sa(len, 124);
        printf("%I64d\n", sa.solve(n, len, k));
    }
    return 0;
}