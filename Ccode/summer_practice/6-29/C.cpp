#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;

int a[maxn], b[maxn];
int dp[maxn][20];
void init(int n){
    for(int i = 1; i <= n; ++i){
        dp[i][0] = a[i];
    }
    for(int j = 1; (1 << j) <= n; ++j){
        for(int i = 1; i + (1 << j) - 1 <= n; ++i){
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}

inline int rmq(int l, int r){
    int k = 31 - __builtin_clz(r - l + 1);
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int main(){
    int T, n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
            b[i] = 0;
        }
        init(n);
        for(int i = 2; i <= n; ++i){
            for(int j = i; j <= n; j += i){
                b[i] = max(b[i], rmq(j - i + 1, j - 1));
                if(j + i > n && j + 1 <= n){
                    b[i] = max(b[i], rmq(j + 1, n));
                }
            }
        }
        for(int i = 2; i <= n; ++i){
            printf("%d%c", b[i], (i == n) ? '\n' :' ');
        }
    }
    return 0;
}