#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50;
ll a[maxn][maxn];
vector<int> v1, v2;
int n;
ll dfs(int depth = 0)
{
    if(depth == n * 2)  return 0;
    ll ans = LLONG_MAX;
    if(v1.size() < n)
    {
        ll cur = 0;
        for(int i: v1) cur += a[i][depth];
        v1.push_back(depth);
        ans = min(ans, cur + dfs(depth + 1));
        v1.pop_back();
    }
    if(v2.size() < n)
    {
        ll cur = 0;
        for(int i:v2) cur += a[i][depth];
        v2.push_back(depth);
        ans = min(ans, cur + dfs(depth + 1));
        v2.pop_back();
    }
    return ans;
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < 2 * n; i++)
        for(int j = 0; j < 2 * n; j++)
            scanf("%lld", &a[i][j]);
    ll ans = 0;
    for(int i = 0; i < 2 * n; i++)
        for(int j = i + 1; j < 2 * n; j++)
            ans += a[i][j];
    ans -= dfs();
    printf("%lld\n", ans);
    return 0;
}