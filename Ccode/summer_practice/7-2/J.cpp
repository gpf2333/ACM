#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int a[maxn], b[maxn];
bool inline check(const int n, const int m){
    return ((n & m) == m) ? 1 : 0;
}
int main(){
    int T, n, m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
            b[i] = a[i];
        }
        for(int i = 2; i <= n; ++i){
            if(check(m + i - 2, i - 1)){
                for(int j = i; j <= n; ++j){
                    b[j] ^= a[j - i + 1];
                }
            }
        }
        for(int i = 1; i <= n; ++i){
            printf("%d%c", b[i], (i == n) ? '\n' : ' ');
        }
    }
    return 0;
}