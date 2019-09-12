#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ll n, k, m;
    int t;
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        ll tmp = m / (n - k + 1);
        ll ans = (tmp + 1) * k + tmp * (n - k) + m % (n - k + 1);
        cout << ans << endl;
    }
    return 0;
}