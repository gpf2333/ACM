#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int cnt[maxn];
struct Node{
    int val, id;
}a[maxn];

bool cmp(const Node &a, const Node &b){
    if(a.id == b.id) return a.val < b.val;
    return a.id > b.id;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i].val);
        a[i].id = 0;
    }
    for(int i = 1; i <= m; ++i){
        int x;
        scanf("%d", &x);
        a[x].id = i;
    }
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; ++i){
        printf("%d ", a[i].val);
    }
    return 0;
}