#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;
int n, a[maxn];
int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &a[i]);
    }
    int up = (1 << n), ans = 1;
    for(int i = 1; i <= up; ++i){
        int cnt = 0, tmp;
        for(int j = 0; j < n; ++j){
            if(i & (1 << j)){
                ++cnt;
                if(cnt == 1) tmp = a[j];
                else tmp = gcd(tmp, a[j]);
            }
        }
        if(tmp > 1) ans = max(ans, cnt);
    }
    printf("%d\n", ans);
    return 0;
}

