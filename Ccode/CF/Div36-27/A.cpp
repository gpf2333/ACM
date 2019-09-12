#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}
bool check(int n){
    int res = 0;
    while(n){
        res += (n % 10);
        n /= 10;
    }
    return (res % 4 == 0);
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i = n; ; ++i){
        if(check(i)){
            printf("%d\n", i);
            break ;
        }
    }
    return 0;
}