#include<bits/stdc++.h>
using namespace std;
const int maxn = 200;
const int INF = 0x3f3f3f3f;
bool vis[2][4][2][maxn];
int n, a[maxn];
void calc(int a, int b, int c){
    for(int i = 0; i <= a; ++i){
        for(int j = 0; j <= b; ++j){
            for(int k = 0; k <= c; ++k){
                vis[a][b][c][i * 10 + j * 20 + k * 50] = 1;
            }
        }
    }
}

void init(){
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i <= 1; ++i){ //10 up 1
        for(int j = 0; j <= 3; ++j){//20 up 3
            for(int k = 0; k <= 1; ++k){//50 up 1
                calc(i, j, k);
            }
        }
    }
}

int check(int x, int y, int z){
    int sum = 0, res = 0;
    for(int i = 1; i <= n; ++i){
        if(a[i] >= 100 && vis[x][y][z][a[i] % 100 + 100]){
            res = (a[i] - a[i] % 100 - 100) / 100;
        }else if(vis[x][y][z][a[i] % 100]){
            res = (a[i] - a[i] % 100) / 100;
        }else{
            res = INF;
        }
        sum = max(sum, res);
    }
    return sum;
}

int main(){
    init();
    int T;
    scanf("%d", &T);
    while(T--){
        bool ok = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            if(a[i] % 10) ok = 1;
        }
        if(ok){
            puts("-1"); continue ;
        }
        int ans = INF;
        for(int i = 0; i <= 1; ++i){
            for(int j = 0; j <= 3; ++j){
                for(int k = 0; k <= 1; ++k){
                    ans = min(ans, check(i, j, k) + i + j + k);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
