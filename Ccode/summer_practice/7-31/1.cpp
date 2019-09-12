#include<bits/stdc++.h>
using namespace std;
const int maxn = 4000 + 10;
typedef long long ll;
bool isprime[maxn];
int cntp, prime[maxn];

void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0) break ;
        }
    }
}

int main(){
    init();
    int T; 
    ll n;
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &n);
        ll tmp = n;
        int ans = 64;
        for(int i = 1; i <= cntp && prime[i] <= tmp; ++i){
            if(tmp % prime[i] == 0){
                int c = 0;
                while(tmp % prime[i] == 0){
                    ++c, tmp /= prime[i];
                }
                ans = min(ans, c);
            }
        }
        if(tmp == 1 || ans == 1){
            printf("%d\n", ans);
            continue ;
        }
        ll tmp1 = (ll)(pow(tmp, 1.0 / 4.0) + 0.5);
        ll tmp2 = (ll)(pow(tmp, 1.0 / 3.0) + 0.5);
        ll tmp3 = (ll)(sqrt(tmp) + 0.5);
        if(tmp1 * tmp1 * tmp1 * tmp1 == tmp) ans = min(ans, 4);
        else if(tmp2 * tmp2 * tmp2 == tmp) ans = min(ans, 3);
        else if(tmp3 * tmp3 == tmp) ans = min(ans, 2);
        else ans = min(ans, 1);
        printf("%d\n", ans);
    }
    return 0;
}