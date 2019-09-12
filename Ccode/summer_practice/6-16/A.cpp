#include<bits/stdc++.h>
using namespace std;
const int maxn = 200 + 5;
const int INF = 0x3f3f3f3f;
char s[maxn][maxn];
int n, m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; ++i){
        scanf("%s", s[i]);
    }
    double sumx = 0, leftx, rightx;
    int cnt = 0, last = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(s[i][j] != '.'){
                last = i;
                ++cnt;
                sumx += (j * 1.0 + 0.5);
            }
        }
    }
    sumx = sumx / (cnt * 1.0);
    for(int i = 0; i < m; ++i){
        if(s[last][i] != '.'){
            leftx = i * 1.0;
            break ;
        }
    }
    for(int i = m - 1; i >= 0; --i){
        if(s[last][i] != '.'){
            rightx = (i * 1.0) + 1.0;
            break ;
        }
    }
    if(sumx < leftx){
        puts("left");
    } else if(sumx > rightx){
        puts("right");
    } else{
        puts("balanced");
    }
    return 0;
}
