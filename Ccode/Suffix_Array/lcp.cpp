#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 500000 + 100;

/*
求height[i]数组上的每一个区间的最小值之和
dp[i]为height数组中前缀i的每一个后缀贡献出的答案。

*/
ll dp[maxn];
struct Suffix_Array{
    char s[maxn];
    int sa[maxn], rk[maxn], t[maxn], t2[maxn], c[maxn],height[maxn];
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
            swap(x, y);
            p = 1; // note!!!
            x[sa[0]] = 0;
            for(int i = 1; i < n; ++i){
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? (p - 1): p++;
            }
            if(p >= n) break ;
            m = p;
        }
        --n;
        for(int i = 0; i <= n; ++i) rk[sa[i]] = i;
        for(int i = 0, k = 0; i < n; ++i){
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }

    ll calc(int n){
        for(int i = 0; i <= n; ++i) dp[i] = 0;
        stack<int>sta;
        ll res = 0;
        for(int i = 1; i <= n; ++i){
            while(!sta.empty() && height[sta.top()] > height[i]) sta.pop();
            if(!sta.empty()){
                int p = sta.top();
                dp[i] = dp[p] + (ll)(i - p) * height[i];
            }else{
                dp[i] = (ll) i * height[i];
            }
            res += dp[i];
            sta.push(i);
        }
        return res;
    }

}sa;

int main(){
    while(~scanf("%s", sa.s)){
        int n = strlen(sa.s);
        sa.build_sa(n, 130);
        ll ans = ((ll)n * (n + 1) * (n - 1)) / 2 - 2LL * sa.calc(n);
        printf("%lld\n", ans);
    }
    return 0;
}