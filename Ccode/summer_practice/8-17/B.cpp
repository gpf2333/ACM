#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 60;
const ll INF = 1e12;
ll f[maxn];
string s1 = "COFFEE";
string s2 = "CHICKEN";
int init(){
    f[1] = 6, f[2] = 7;
    for(int i = 3; ; ++i){
        f[i] = f[i - 2] + f[i - 1];
        if(f[i] > INF){
            return i;
        }
    }
}

void dfs(int n, ll l, ll r){
    if(n == 1){
        for(int i = l; i <= min(6LL, r); ++i){
            putchar(s1[i - 1]);
        }
        return ;
    }
    if(n == 2){
        for(int i = l; i <= min(7LL, r); ++i){
            putchar(s2[i - 1]);
        }
        return ;
    }
    if(f[n - 2] >= r){
        dfs(n - 2, l, r);
        return ;
    }
    if(l > f[n - 2]){
        dfs(n - 1, l - f[n - 2], r - f[n - 2]);
        return ;
    }
    dfs(n - 2, l, f[n - 2]); // (l, f[n - 2]) + (1, r - f[n - 2])
    dfs(n - 1, 1, r - f[n- 2]); //note (1, r - f[n- 2])
    return ;
}

int main(){
    int cnt = init();
    int T, n;
    ll k;
    scanf("%d", &T);
    while(T--){
        scanf("%d%lld", &n, &k);
        dfs(min(n, cnt), k, k + 9);
        puts("");
    }
    return 0;
}