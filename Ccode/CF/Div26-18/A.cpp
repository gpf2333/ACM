#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
ll gcd(ll a, ll b){
    return (b == 0) ? a : gcd(b, a % b);
}
char a[maxn], b[maxn];
bool vis[300];
int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s%s",a, b);
        int lena = strlen(a);
        int lenb = strlen(b);
        if(lena > lenb || a[0] != b[0]){
            puts("NO");
            continue ;
        }
        bool ok = true;
        int i = 1, j = 1;
        for(; i < lena && j < lenb; ++i, ++j){
            while(b[j] == a[i -1] && a[i - 1] != a[i]){
                ++j;
            }
            if(b[j] != a[i]){
                ok = false; break;
            }
        }
        if(!ok){
            puts("NO");
            continue ;
        }
        for(; j < lenb; ++j){
            if(b[j] != a[lena - 1]){
                ok = false; break;
            }
        }
        if(!ok || i < lena){
            puts("NO");
        }else{
            puts("YES");
        }
    }
}

// int main(){
//     int a, b, c, d;
//     cin >> a >> b >> c >> d;
//     int x  = min(a, min(b, c));
//     int z  = max(a, max(b, c));
//     int y = a + b + c - x - z;
//     ll ans = 0;
//     if(y - x < d){
//         ans += d - (y -x);
//     }
//     if(z - y < d){
//         ans += d - (z - y);
//     }
//     cout << ans << endl;
//     return 0;
// }