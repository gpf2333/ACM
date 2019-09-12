#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
struct SuffixArray{
    char s[maxn];
    int sa[maxn], rk[maxn], tp[maxn], c[maxn], height[maxn];

    void radixsort(int n, int m)
    {
        for(int i = 0; i <= m; ++i) c[i] = 0;
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
                rk[sa[i]] = (tp [sa[i]] == tp[sa[i - 1]] && tp[sa[i] + k] == tp[sa[i - 1] + k]) ? p : ++p;
            }
            if(p >= n) break;
            m = p;
        }
        int k = 0;
        for(int i = 1; i <= n; ++i)
        {
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }

    int dp[maxn][23];
    void initrmq(const int n){
        for(int i = 1; i <= n; ++i) dp[i][0] = height[i];
        for(int j = 1; (1 << j) <= n; ++j){
            for(int i = 1; i + (1 << j) - 1 <= n; ++i){
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int rmq(const int l, const int r){
        int k = 31 - __builtin_clz(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }

    ll solve(int n, int k){
        ll ans = 0;
        height[n + 1] = 0;
        if(k == 1){
            for(int i = 1; i <= n; ++i){
                ans += max(0, (n - sa[i] + 1) - max(height[i], height[i + k]));
            }
        }else{
            initrmq(n);
            for(int i = 1; i + k - 1 <= n; ++i){
                ans += max(0, rmq(i + 1, i + k - 1) - max(height[i], height[i + k]));
            }
        }
        return ans;
    }

}sa;
int main(){
    int T, k;
    scanf("%d", &T);
    while(T--){
        scanf("%d%s", &k, sa.s + 1);
        int n = strlen(sa.s + 1);
        sa.build_sa(n, 256);
        printf("%lld\n", sa.solve(n, k));
    }
    return 0;
}