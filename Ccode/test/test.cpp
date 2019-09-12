#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
bool isprime[maxn];
int cntp, prime[maxn];
unordered_map<ll, bool>mp;

void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[1] = isprime[0] = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            mp[(ll)i * i] = 1;
            prime[++cntp] = i;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                break ;
            }
        }
    }
}

int main(){
    init();
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    while(n--){
        ll x;
        cin >> x;
        if(mp.count(x)){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}