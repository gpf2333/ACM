#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;
using namespace std;
const int maxn = 1e6 + 5;
ll a[maxn],b[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while(T --)
    {
        int n;
        cin >> n;
        ll sum = 0;
        ll ans = 0;
        for(int i = 1; i <= n; i++)
        {
            cin >> a[i] >> b[i];
            sum += b[i];
        }
        ll pre = 0;
        ll last = 0;
        for(int i = 1; i <= n; i++){
            pre = last;
            if(pre >= b[i]){
                pre -= b[i];
            }
            else{
                b[i] -= pre;
            }
            if(sum - pre - b[i] >= a[i]){
                last += a[i];
                ans += a[i];
            }
            else{
                last += sum - pre - b[i];
                ans += sum - pre - b[i];
            }
        }
        cout << ans << endl;
    }
}

/*
1
3
3 1
3 5
3 0

1
5
1 2
3 6
2 5
3 1
2 2

*/