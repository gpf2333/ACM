// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;

// ll gcd(ll a, ll b){
//     return b == 0 ? a : gcd(b, a % b);
// }

// int main(){
//     int T, n, m, p;
//     scanf("%d", &T);
//     while(T--){
//         scanf("%d%d%d", &n, &m, &p);
//         if(n > m) swap(n, m);
//         int x = n / p;
//         int rem = n % p;
//         ll ans = 0;
//         for(int r = 0; r < p && r <= n; ++r){
//             int tmp = (m / (p / gcd(p, r)));
//             int cnt = 0;
//             if(r == 0) cnt = x;
//             else if(r <= rem) cnt = (x + 1);
//             else cnt = x;
//             ans += (ll)cnt * tmp;
//             // cout << r << " " << cnt << " " << tmp << endl;
//         }
//         printf("%lld\n", ans);
//     }
//     return 0;
// }

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn=1e5+5;
ll n,m;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

bool solve(int a,ll b,int c,ll d){
    ll g=gcd(n,m);
    ll t1=n/g,t2=m/g;
    b--;d--;
    if(a==1&&c==1) return (b/t1)==(d/t1);
    else if(a==2&&c==2) return (b/t2)==(d/t2);
    else if(a==1&&c==2)return (b/t1)==(d/t2);
    else return (b/t2)==(d/t1);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int q;cin>>n>>m>>q;
    while(q--){
        int a,c;ll b,d;cin>>a>>b>>c>>d;
        if(solve(a,b,c,d)) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}