#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n, kase = 0;
    while(scanf("%d", &n)){
        if(!n) break ;
        if(n == 1){
            printf("Case %d: %d\n", ++kase, 2);
            continue ;
        }
        int cnt = 0, tmp, up = sqrt(n);
        ll ans = 0;
        for(int i = 2; i <= up; ++i){
            if(n % i == 0){
                ++cnt;
                tmp = 1;
                while(n % i == 0){
                    tmp *= i, n /= i;
                }
                ans += tmp;
            }
        }
        if(n > 1){
            ++cnt;
            ans += n;
        }
        if(cnt < 2){
            ++cnt;
            ans += 1;
        }
        printf("Case %d: %lld\n", ++kase, ans);
    }
    return 0;
}