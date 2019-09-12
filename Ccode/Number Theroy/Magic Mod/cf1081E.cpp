#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int up = 2e5 + 10;
ll a[maxn];
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 2; i <= n; i += 2){
        scanf("%lld", &a[i]);
    }
    int ls = 0;
    for(int i = 1; i <= n; i += 2){
        for(int j = ls + 1; j < up; ++j){
            ll ns = (ll)j * j + a[i + 1];
            ll tmp = sqrt((double)ns) + 0.5;
            if(tmp * tmp == ns){
                a[i] = (ll)j * j - (ll)ls * ls;
                ls = tmp;
                break ;
            }
            if((ll)j * j - (ll)(j - 1) * (ll)(j - 1) > a[i + 1]){
                puts("No");
                return 0;
            }
        }
    }
    puts("Yes");
    for(int i = 1; i <= n; ++i){
        printf("%lld ", a[i]);
    }
    puts("");
    return 0;
}