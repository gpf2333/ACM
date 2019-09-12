#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>
#include<queue>
#include<vector>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, cnt;
struct node{
    int l, r; 
    int sum; //[l, r]内管辖的数的个数
    node(){
        sum = 0;
    }
}tree[maxn * 20];
struct VAULUE
{
    int x; //值 
    int id; //离散之前在原数组中的位置
}value[maxn];
bool cmp(const VAULUE &a, const VAULUE &b){
    return a. x < b.x;
}
int root[maxn]; //多颗线段树的根结点
int Rank[maxn]; //原数组离散之后的数组
void init(){
    cnt = 1;
    root[0] = 0;
    tree[0].l = tree[0].r = tree[0].sum = 0;
}
void update(int &rt, int l, int r, int val){
    tree[cnt++] = tree[rt];
    rt = cnt - 1;
    ++tree[rt].sum;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(val <= mid) update(tree[rt].l, l, mid, val);
    else update(tree[rt].r, mid + 1, r, val);
}

int query(int i, int j, int k, int l, int r){
    int d = tree[tree[j].l].sum - tree[tree[i].l].sum;
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(k <= d) return query(tree[i].l, tree[j].l, k, l, mid);
    else return query(tree[i].r, tree[j].r,  k - d, mid + 1, r);
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; ++i){
            scanf("%d", &value[i].x);
            value[i].id = i;
        }
        sort(value + 1, value + n + 1, cmp);
        for(int i = 1; i <= n; ++i){
            Rank[value[i].id] = i;
        }
        init();
        for(int i = 1; i <= n; ++i){
            root[i] = root[i - 1];
            update(Rank[i], root[i], 1, n);
        }
        int l, r, k;
        for(int i = 1; i <= m; ++i){
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", value[query(root[l - 1], root[r], k, 1, n)].x);
        }
    }
    return 0;
}