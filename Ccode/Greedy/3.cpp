#include<bits/stdc++.h>
using namespace std;
int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}
int main(){
    int x, y;
    while(~scanf("%d%d",&x,&y)){
        int n = y / x;
        if(!n || y % x != 0){
            puts("0");
            continue ;
        }
        if(n == 1){
            puts("1");
            continue ;
        }
        int ans = 0;
        for(int i = 1; (long long)i * i < n; ++i){
            if(n % i == 0){
                int p = i, q = n / i;
                if(gcd(p, q) > 1) continue ;
                ans += 2;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}