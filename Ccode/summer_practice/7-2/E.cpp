#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool vis[1000];
int get(int n){
    for(int i = 0; i <= (n + 3); ++i){
        vis[i] = 0;
    }
    int ans = 0;
    for(int i = 1; i <= (n + 3); ++i){
        int tmp = n % i;
        if(!vis[tmp]){
            vis[tmp] = 1;
            ++ans;
        }
    }
    return ans;
}

int main(){
    // for(int i = 1; i <= 100; ++i){
    //     printf("(%d %d)", i, get(i));
    // }
    // puts("");
    int T, a;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&a);
        int ans = 0;
        if((a & 1) == 1){
            ans = (a + 1) / 2 + 1;
        }else{
            ans = a / 2 + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}