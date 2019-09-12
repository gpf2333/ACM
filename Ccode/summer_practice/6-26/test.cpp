#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+10;
int main()
{
    ll n;int caset;
    scanf("%d",&caset);
    while(caset--) {
        scanf("%lld",&n);
        ll res = 0;
        for(int i=1;i<=n;) {
            int r = n/(n/i)+1;
            res += (n/i) * (r - i);
            i = r;
        }
        printf("%lld\n",res);
    }
    return 0;
}

