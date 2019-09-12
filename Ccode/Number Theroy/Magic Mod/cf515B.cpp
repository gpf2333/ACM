#include<bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
bool vis[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    int d = __gcd(n, m);
    for(int i = 0; i < 2; ++i){
        int t;
        cin >> t;
        for(int j = 0; j < t; ++j){
            int x;
            cin >> x;
            vis[x % d] = 1;
        }
    }
    for(int i = 0; i < d; ++i){
        if(!vis[i]){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}