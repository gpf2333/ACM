#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int maxn = 2e4 + 100;
struct Suffixarray{
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
            for(int i = 1; i < m; ++i) c[i] += c[i - 1];
            for(int i = n - 1; ~i; --i) sa[--c[x[y[i]]]] = y[i];
            std::swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for(int i = 1; i < n; ++i){
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1: p++;
            }
            if(p >= n) break ;
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

    int dp[maxn][21];
    void initrmq(int n){
        for(int i = 1; i <= n; ++i) dp[i][0] = height[i];
        for(int j = 1; (1 << j) <= n; ++j){
            for(int i = 1; i + (1 << j) - 1 <= n; ++i){
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int rmq(int l, int r){
        int k = 31 - __builtin_clz(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
    
    bool check(int x, int n, int k){
        int cnt = 0;
        for(int i = 0; i <= n; ++i){
            if(height[i] >= x){
                ++cnt;
            }else{
                cnt = 1;
            }
            if(cnt >= k) return 1;
        }
        return 0;
    }

    int solve(int n, int k){
        int l = 0, r = n, mid, ans;
        while(l <= r){
            mid = (l + r) >> 1;
            if(check(mid, n, k)){
                ans = mid;
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        return ans;
    }

}sa;

map<int, int>mp;
int a[maxn];
int main(){
    int n, k;
    while(~scanf("%d%d",&n,&k)){
        mp.clear();
        int val = 1;
        for(int i = 0; i < n; ++i){
            scanf("%d",&a[i]);
            if(!mp[a[i]]){
                mp[a[i]] = val++;
            }
        }
        for(int i = 0; i < n; ++i){
            sa.s[i] = mp[a[i]];
        }
        sa.build_sa(n, val);
        printf("%d\n", sa.solve(n, k));
    }
    return 0;
}