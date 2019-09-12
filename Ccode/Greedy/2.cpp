#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 10;
struct Node{
    int cost, num;
}a[maxn];
bool cmp(const Node &a, const Node &b){
    if(a.cost == b.cost) return a.num > b.num;
    return a.cost < b.cost;
}
int main(){
    int n, m;
    while(~scanf("%d%d",&n,&m)){
        for(int i = 0; i < m; ++i){
            scanf("%d%d",&a[i].cost, &a[i].num);
        }
        sort(a, a + m, cmp);
        int sum = 0;
        long long ans = 0;
        for(int i = 0; i < m; ++i){
            if(sum + a[i].num <= n){
                sum += a[i].num;
                ans += (long long)a[i].cost * a[i].num;
            }else{
                ans += (long long)a[i].cost * (n - sum);
                break ;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}