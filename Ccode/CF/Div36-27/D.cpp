#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
const int INF = 1e7;
int a[maxn];
int cnt[maxn], rk[maxn];
int main(){
    int q, n;
    scanf("%d",&q);
    while(q--){
        scanf("%d",&n);
        for(int i = 0; i <= n; ++i){
            cnt[i] = rk[i] = 0;
        }
        int len = 1;
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
            if(!rk[a[i]]){
                rk[a[i]] = len;
                ++cnt[len];
                len++;
            }else{
                ++cnt[rk[a[i]]];
            }
        }
        sort(cnt + 1, cnt + len);
        int ans = cnt[len - 1], maxx = cnt[len - 1];
        for(int i = len - 2; i >= 1; --i){
            if(cnt[i] >= maxx){
                ans = ans + (maxx - 1);
                maxx -= 1; 
                if(!maxx) break ;
            }else{
                ans += cnt[i];
                maxx = cnt[i];
            }
        }
        printf("%d\n", ans);
    }
}