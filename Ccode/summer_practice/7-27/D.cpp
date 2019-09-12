#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int T;
    long long n;
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &n);
        if(n % 3 == 0){
            printf("1 %lld\n", n);
            continue ;
        }
        int c = n & 1;
        ll x, y;
        for(ll i = n - 1; i >= 3; --i){
            if(i % 3 == 0){
                if(c == 0 && (i % 2) == 1){
                    x = i - 3; 
                }else{
                    x = i;
                }
                break ;
            }
        }
        for(ll i = 3; i <= n; i += 3){
            if((x | i) == n){
                y = i; break ;
            }
        }
        if(x > y) swap(x, y);
        printf("2 %lld %lld\n", x, y);
    }
    // ll n;
    // int a[70];
    // while(cin >> n){
    //     ll x = n;
    //     int c = 0;
    //     while(x){
    //         a[c++] = x & 1;
    //         x >>= 1;
    //     }
    //     reverse(a, a + c);
    //     for(int i = 0; i < c; ++i){
    //         printf("%d", a[i]);
    //     }
    //     puts("");
    // }
    return 0;
}

/*
1111210
*/