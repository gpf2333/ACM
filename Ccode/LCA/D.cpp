#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 998244353;
struct Node{
    int val;
    int sum1;
    int sum2;
}a[maxn];

int get1(int n, int &len){
    int res = 0;
    int tmp = 1;
    int len = 0;
    while(n){
        res = (((ll)res +  (ll)(n % 10) * tmp % mod) % mod;
        ++len;
        
    }
}

int main(){
    int n;
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i].val);
        }
    }
    return 0;
}