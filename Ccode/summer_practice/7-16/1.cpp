#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll calc(int n){
    ll res = 0;
    for(int l = 1, r; l <= n;l = r + 1){
        r = n / (n / l);
        res += (n / l) * (r - l + 1);
    }
    return res;
}

int main(){
    int T, kase = 0;
    int n;
    scanf("%d", &T);
    while(T--){
        scanf("%d",&n);
        ll res = calc(n);
        cout << res << endl;
        printf("Case %d: %s\n", ++kase, (res & 1) ? "odd": "even");
    }
    return 0;
}