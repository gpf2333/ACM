#include<bits/stdc++.h>
using namespace std;
const int maxn = 100 + 10;
int cnt[maxn];
int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; ++i){
        int x;
        scanf("%d", &x);
        ++cnt[x % k];
    }
    int ans = 0;
    ans += 2 * (cnt[0] / 2);
    int up = (k % 2 == 0) ? (k / 2 - 1) : (k / 2);
    for(int i = 1; i <= up; ++i){
        ans += 2 * min(cnt[i], cnt[k - i]);
    }
    if(k % 2 == 0) ans += 2 * (cnt[k / 2] / 2);
    printf("%d\n", ans);
    return 0;
}