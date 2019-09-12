#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
struct SuffixArray{
    char s[maxn];
    int sa[maxn], rk[maxn], tp[maxn],c[maxn],height[maxn];

    void radixsort(int n, int m)
    {
        for(int i = 0; i<= m; ++i) c[i] = 0;
        for(int i = 1; i <= n; ++i) ++c[rk[i]];
        for(int i = 1; i <= m; ++i) c[i] += c[i - 1];
        for(int i = n; i >= 1; --i) sa[c[rk[tp[i]]]--] = tp[i];
    }

    void build_sa(int n, int m){
        for(int i = 1; i <= n; ++i){
            rk[i] = s[i], tp[i] = i;
        }
        radixsort(n, m);
        for(int k = 1; k <= n; k <<= 1){
            int p = 0;
            for(int i = n - k + 1; i <= n; ++i) tp[++p] = i;
            for(int i = 1; i <= n; ++i){
                if(sa[i] > k) tp[++p] = sa[i]-k;
            }
            radixsort(n, m);
            std::swap(rk, tp);
            p = rk[sa[1]] = 1;
            for(int i = 2; i <= n; ++i){
                rk[sa[i]] = (tp [sa[i]] == tp[sa[i - 1]] && tp[sa[i] + k] == tp[sa[i - 1]+k]) ? p : ++p;
            }
            if(p >= n) break;
            m = p;
        }
        int k = 0;
        for(int i = 1; i <= n; ++i)
        {
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(i + k <= n && j +k <= n && s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }
}sa;
int main(){
    while(~scanf("%s",sa.s + 1)){
        int n = strlen(sa.s + 1);
        sa.build_sa(n, 256);
        for(int i = 1; i <= n; ++i){
            printf("%d%c", sa.sa[i], (i == n) ? '\n' : ' ');
        }
    }
    return 0;
}