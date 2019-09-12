#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3000 + 5;
char s[maxn], t[maxn];
int main(){
    int T;
    int m, n;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        scanf("%s%s", s, t);
        if(n == m){
            if(strcmp(s, t) > 0){
                puts("1");
            }else{
                puts("0");
            }
            continue ;
        }
        int up = n - m;
        ll ans = 0;
        for(int i = 0; i < up; ++i){
            int p = i, q = 0;
            while(p < n && q < m){
            }
        }
    }
    return 0;
}