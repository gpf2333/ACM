#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10;
int s[maxn << 1], temp[maxn << 1];
int p[maxn << 1];
int solve(int n){
    temp[0] = -1; 
    for(int i = 1; i <= n; ++i){
        temp[2 * i - 1] = 0;
        temp[2 * i] = s[i];
    }
    temp[(n << 1) + 1] = 0;
    n = 2 * n + 1;
    int mx = 0, id = 0, res = 1;
    p[0] = 0;
    for(int i = 1; i < n; ++i){
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while(temp[i - p[i]] == temp[i + p[i]] && temp[i - p[i]] <= temp[i - p[i] + 2]){
            ++p[i];
        }
        if(i + p[i] > mx){
            id = i;
            mx = i + p[i];
        }
        if(res < p[i] - 1){
            res = p[i] - 1;
        }
    }
    return res;
}
int main(){
    int T, n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i = 1; i <= n; ++i){
            scanf("%d",&s[i]);
        }
        printf("%d\n", solve(n));
    }
    return 0;
}