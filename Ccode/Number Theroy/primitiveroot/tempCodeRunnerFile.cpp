#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int qpow(int a, int b, const int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}
vector<int>fac;
void get_fac(int n){
    fac.clear();
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            fac.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) fac.push_back(n);
}
bool is_p_root(const int x, const int p, const vector<int> &fac){
    for(auto &v: fac){
        if(qpow(x, (p - 1) / v, p) == 1) return false;
    }
    return true;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int p;
    cin >> p;
    get_fac(p - 1);
    int ans = 0;
    for(int i = 2; i <= p - 1; ++i){
        if(is_p_root(i, p, fac)){
            ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}