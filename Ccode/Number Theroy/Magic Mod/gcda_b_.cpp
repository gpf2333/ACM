#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p[] = {2, 3, 5, 7, 11};

int calc(int x, int p){
    int res = 0;
    while(x){
        res += x / p;
        x /= p;
    }
    return res;
}

int qpow(int a, int b){
    int res = 1;
    while(b > 0){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main(){
    int a, b;
    scanf("%d%d", &a, &b);
    int ans = 1;
    for(int i = 0; i < 5; ++i){
        ans = ans * qpow(p[i], min(calc(a, p[i]), calc(b, p[i])));
    }
    printf("%d\n", ans);
    return 0;
}