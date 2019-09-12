// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// int main(){
//     ll x, y, z;
//     cin >> x >> y >> z;
//     ll sum = (x + y) / z;
//     cout << sum << " ";
//     if(sum == 0){
//         cout << 0 << endl;
//         return 0;
//     }
//     ll mx = x % z;
//     ll my = y % z;
//     if(mx == 0 || my == 0){
//         cout << 0 << endl;
//     }
//     ll lx = z - mx;
//     ll ly = z - my;
//     cout << min(lx, ly) << endl;
//     return 0;
// }

// C
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
int cnt[maxn][maxn];
char s[maxn][maxn];
int main(){
    int n, m;
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; ++i){
        scanf("%s", s[i]);
    }
    for(int j = 0; j < m; ++j){
        for(int i = n - 1; i >= 0; --i){
            if(i == n - 1) cnt[i][j] = 1;
            else{
                cnt[i][j] = (s[i][j] == s[i + 1][j]) ? (cnt[i + 1][j] + 1) : 1;
            }
        }
    }
    ll ans = 0, tmp = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            int len = cnt[i][j];
            if(i + len * 3 <= n && cnt[i + len][j] == len && cnt[i + len * 2][j] >= len){
                if(j > 0 && s[i][j - 1] == s[i][j] && s[i + len][j - 1] == s[i + len][j] 
                && s[i + 2 * len][j - 1] == s[i + 2 * len][j] && cnt[i][j - 1] == len 
                && cnt[i + len][j - 1] == len && cnt[i + 2 * len][j - 1] >= len){
                    ++tmp;
                    ans += tmp;
                } else {
                    ++ans;
                    tmp = 1;
                }
            } else {
                tmp = 0;
            }
        }
    }
    cout << ans << endl;
    return 0;
}