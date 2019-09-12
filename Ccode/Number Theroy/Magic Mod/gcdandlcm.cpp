#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
ll calc(int n){
    ll ans = 1;
    for(int i = 2; i <= n; ++i){
        if(n % i == 0){
            int cnt = 0;
            while(n % i == 0) n /= i, ++cnt;
            // cout << i << " " << cnt << endl;
            ans *= 6 * cnt;
        }
    }
    if(n > 1){
        ans *= 6;
    }
    return ans;
}

int main(){
    int T;
    int a, b;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &a, &b);
        if(b % a){
            puts("0");
        }else{
            printf("%lld\n", calc(b / a));
        }
    }
    return 0;
}