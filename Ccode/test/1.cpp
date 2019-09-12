#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
typedef long long ll;

struct Node{
    int x, y;
}a[maxn];

bool cmp(const Node &a, const Node & b){
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

int b[maxn];
bool vis[maxn];

int main(){
    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for(int i = 1; i <= k; ++i){
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    for(int i = 1; i <= q; ++i){
        scanf("%d", &b[i]);
        vis[b[i]] = 1;
    }
    sort(a + 1, a + 1 + k);
    
    sort(b + 1, b + + 1 + q);
    ll ans = 0;
    int lasx = 1, lasy = 1;    
    for(int i = 1; i <= k; ){
        if(lasx == a[i].x){
            while(i + 1 <= k && a[i].x == a[i + 1].x){
                ++i;
            }
            ans += (a[i].y - lasy);
            lasy = a[i].y;
            ++i;
            if(i > k) break ;
        }else{

        }
    }
    return 0;
}