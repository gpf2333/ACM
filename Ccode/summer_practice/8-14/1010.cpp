#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct node{
    string id;
    int s;
    int p;
    bool operator <(const node &n1) const{
        if(s == n1.s) return p < n1.p;
        return s > n1.s;
    }
}a[maxn];
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--){
        int n, rate;
        cin >> n >> rate;
        for(int i = 1; i <= n; i++){
            cin >> a[i].id >> a[i].s >> a[i].p;
        }
        sort(a + 1, a + 1 + n);
        int r = n *  rate;
        if(r % 10 == 5){
                cout << a[r / 10 + 1].id << endl;
        }
        else{
            cout << "Quailty is very great" <<endl;
        }
    }
}