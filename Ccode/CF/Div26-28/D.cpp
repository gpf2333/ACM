#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;
double a[maxn];
int b[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    while(cin >> n){
        ll res = 0;
        for(int i = 1; i <= n; ++i){
            cin >> a[i];
            b[i] = (int)floor(a[i]);
            res += b[i];
        }
        if(res < 0){
            for(int i = 1; i <= n; ++i){
                if(floor(a[i]) != ceil(a[i])){
                    ++b[i];
                    ++res;
                    if(!res) break ;
                }
            }
        }
        for(int i = 1; i <= n; ++i){
            cout << b[i] << endl;
        }
    }
    return 0;
}