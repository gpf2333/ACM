#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e3 + 50;
int a[maxn];

bool check(int n, int x){
    for(int i = 1; i <= n; ++i){
        if(x % a[i]) return 0;
    }
    return 1;
}

int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        int mx = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            if(a[i] > mx) mx = a[i];
        }
        int up = 10 * m;
        int tmp = -1;
        for(int i = mx; i <= up; ++i){
            if(check(n, i)){
                tmp = i;
                 break ;
            }
        }
        if(tmp == -1){
            puts("No");
            continue ;
        }
        int res = 0;
        for(int i = 1; i <= n; ++i){
            res += tmp / a[i];
        }
        if(m % res){
            puts("No");
            continue ;
        }else{
             puts("Yes");
             int ans = m / res;
             printf("%d", ans * (tmp / a[1]));
             for(int i = 2; i <= n; ++i){
                 printf(" %d", ans * (tmp / a[i]));
             }
             puts("");
        }
    }
    return 0;
}