#include<bits/stdc++.h>
using namespace std;
const int mod = 86400 >> 1;
const int maxn = mod + 5;
const int INF = 0x3f3f3f3f;
bool vis[maxn];
int a[maxn];

int getval(const int h, const int m, const int s){
    return (h * 3600 + m * 60 + s) % mod;
}

int main(){
    int n, h, m, s;
    while(~scanf("%d", &n)){
        memset(vis, 0, sizeof(vis));
        scanf("%d%d%d", &h, &m, &s);
        int cur = getval(h, m, s);
        vis[cur] = 1;
        for(int i = 0; i < n; ++i){
            scanf("%d%d%d", &h, &m, &s);
            vis[getval(h, m, s)] = 1;
        }
        int cnt = 0;
        for(int i = 0; i < maxn; ++i){
            if(vis[i]){
                a[cnt++] = i;
            }
        }
        int ans = INF, up = cnt - 1;
        for(int i = 0; i < up; ++i){
            int l = a[i], r = a[i + 1];
            if(r <= cur){
                int dl = (mod - cur + l), dr = cur - r;
                ans = min(ans, min(2 * dl + dr, dl + 2 * dr));
            }else{
                int dl = l - cur, dr = (mod - r + cur);
                ans = min(ans, min(2 * dl + dr, dl + 2 * dr));
            }
        }
        int dl = cur - a[0], dr = a[up] - cur;
        ans = min(ans, min(2 * dl + dr, dl + 2 * dr));
        printf("%.2lf\n", (double)ans * 6.00);
    }
    return 0;
}