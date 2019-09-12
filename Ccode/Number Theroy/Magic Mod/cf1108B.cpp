#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e4 + 10;
int a[maxn];
bool vis[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    int x = 0, y = 0;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        x = max(x, a[i]);
    }
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; ++i){
        if(!vis[a[i]] && __gcd(x, a[i]) == a[i]){
            vis[a[i]] = 1;
        }else{
            y = max(y, a[i]);
        }
    }
    cout << x << " " << y << endl;
    return 0;
}