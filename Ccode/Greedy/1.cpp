#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 50;
int a[maxn];
int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
        }
        int ans = 1, sum = 0;
        for(int i = 1; i <= n; ++i){
            if(sum + a[i] <= m){
                sum += a[i];
            }else{
                ++ans;
                sum = a[i];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}