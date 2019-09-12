#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
int a[maxn];

ll calc(int n){
    ll ans = 0;
    for(int i = 0; i < n; ++i){
        for(int j = i; j < n; ++j){
            int tmp = 0;
            for(int k = i; k <= j; ++k){
                tmp += a[k];
            }
            if(tmp > 0) ++ans;
        }
    }
    return ans;
}

int main(){
    int n, m;
    while(cin >> n){
        memset(a, -1, sizeof(a));
        for(int i = 0; i < n; ++i){
            int l, r;
            cin >> l >> r;
            for(int j = l; j <=r; ++j){
                a[j] = 1;
            }
        }
        cout << calc(100) << endl;
    }
    return 0;
}
