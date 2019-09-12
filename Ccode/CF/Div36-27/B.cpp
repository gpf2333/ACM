#include<bits/stdc++.h>
using namespace std;
const int maxn = 150;
const int INF = 1e9;
int a[maxn];
bool check(int n, int b, int k){
    for(int i = 1; i <= n; ++i){
        if(abs(a[i] - b) > k){
            return false;
        }
    }
    return true;
}
int main(){
    int q, n, k;
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&n,&k);
        int minn = INF, maxx = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
            minn = min(minn, a[i]);
            maxx = max(maxx, a[i]);
        }
        int d = abs(maxx - minn);
        if(d > 2 * k){
            printf("-1\n");
            continue ;
        }else{
            printf("%d\n", minn + k);
        }
    }
    return 0;
}