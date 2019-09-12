#include<bits/stdc++.h>
using namespace std;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson
typedef long long ll;
const int maxn = 1e5 + 100;

int n, d;
struct Node{
    int L, R;
    int val;
}tree[maxn << 4];

int cnty[maxn << 2];
vector< vector<int> > ax(maxn << 2);

void pushup(int rt){
    tree[rt].val = max(tree[lson].val, tree[rson].val);
}

void build(int L, int R, int rt){
    tree[rt].L = L, tree[rt].R = R;
    if(L == R){
        tree[rt].val = cnty[L] + cnty[L + d] + cnty[L + (d << 1)];
        return ;
    }
    int mid = (L + R) >> 1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update(int x, int val, int rt){
    if(tree[rt].L == tree[rt].R && tree[rt]. L == x){
        tree[rt].val += val;
        return ;
    }
    int mid = (tree[rt].L + tree[rt].R) >> 1;
    if(x <= mid) update(x, val, lson);
    else update(x, val, rson);
    pushup(rt);
}

void calc(int x, int val){
    update(x, val, 1);
    if(x - d >= 0) update(x - d, val, 1);
    if(x - 2 * d >= 0) update(x - 2 * d, val, 1);
}

void del(int pos){
    for(auto &y: ax[pos]) calc(y, -1);
}

void add(int pos){
    for(auto &y: ax[pos]) calc(y, 1);
}

int main(){
    memset(cnty, 0, sizeof(cnty));
    for(int i = 0; i < (maxn << 2); ++i) ax[i].clear();
    scanf("%d%d", &n, &d);
    int x, y, mx = 0, my = 0;
    for(int i = 0; i < n; ++i){
        scanf("%d%d", &x, &y);
        ++cnty[y];
        ax[x].push_back(y);
        mx = max(mx, x), my = max(my, y);
    }
    build(0, my, 1); //整个y轴建立一颗线段树
    int ans = 0;
    for(int i = 0; i <= mx; ++i){ //暴力扫x轴
        int tmp = 0;
        if(ax[i].size()){
            tmp += (int)ax[i].size();
            del(i);
        }
        if(ax[i + d].size()){
            tmp += (int)ax[i + d].size();
            del(i + d);
        }
        if(ax[i + (d << 1)].size()){
            tmp += (int)ax[i + (d << 1)].size();
            del(i + (d << 1));
        } //局部去重复交点
        ans = max(ans, tmp + tree[1].val);
        if(ax[i].size()){
            add(i);
        }
        if(ax[i + d].size()){
            add(i + d);
        }
        if(ax[i + (d << 1)].size()){
            add(i + (d << 1));
        } //加回去
    }
    printf("%d\n", ans);
    return 0;
}