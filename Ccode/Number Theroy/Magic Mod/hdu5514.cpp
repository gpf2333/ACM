#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int fac[maxn];
int d[maxn];

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int getphi(int n){
    int res = n;
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            res -= res / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) res -= res / n;
    return res;
}

int main(){
    int T, cas = 0;
    int n, m;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        bool flag = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &d[i]);
            d[i] = gcd(m, d[i]);
            if(d[i] == 1) flag = 1;
        }
        printf("Case #%d: ", ++cas);
        if(flag){
            ll ans = (ll)m * (m - 1) / 2; //note!!!
            printf("%lld\n", ans);
            continue ;
        }
        int cnt = 0;
        for(int i = 2; (ll)i * i <= m; ++i){
            if(m % i == 0){
                if(i * i == m) fac[++cnt] = i;
                else fac[++cnt] = i, fac[++cnt] = m / i;
            }
        }
        sort(fac + 1, fac + 1 + cnt);
        sort(d + 1, d + 1 + n);
        int tot = unique(d + 1, d + 1 + n) - d - 1;
        ll ans = 0;
        for(int i = 1; i <= cnt; ++i){
            for(int j = 1; j <= tot; ++j){
                if(fac[i] % d[j] == 0){
                    ans += (ll)m * getphi(m / fac[i]) / 2;
                    break ;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}