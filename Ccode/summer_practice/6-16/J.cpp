#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
const int maxm = maxn * maxn;

int fa[maxn];
int Find(int x){
    return (x == fa[x]) ? x : (fa[x] = Find(fa[x]));
}

bool Union(int x, int y){
    x = Find(x), y = Find(y);
    if(x != y){
        fa[y] = x;
        return true;
    }
    return false;
}

struct Edge{
    int from, to, next, w;
    bool operator < (const Edge &b){
        return w < b.w;
    }
}edge[maxm];
int head[maxn], tot;

inline void addedge(const int u, const int v, const int w){
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void init(){
    tot = 0;
    memset(head, -1, sizeof(head));
    for(int i = 0; i < maxn; ++i) fa[i] = i;
}

vector<pair<int,int> >vec;
void Krukal(int n){
    sort(edge, edge + tot);
    long long sum = 0;
    if(vec.size() > 0){
        vec.clear();
    }
    int cnt = 0;
    for(int i = 0; i < tot; ++i){
        int u = edge[i].from,  v = edge[i].to;
        if(Union(u, v)){
            ++cnt;
            sum += edge[i].w;
            vec.push_back(make_pair(u, v));
            if(cnt == n - 1) break ;
        }
    }
    cout << sum << endl;
    for(int i = 0; i < vec.size(); ++i){
        printf("%d %d\n", vec[i].first, vec[i].second);
    }
}

char s[maxn][11];
int getw(const char *a, const char *b){
    int w = 0;
    for(int i = 0; a[i]; ++i){
        if(a[i] != b[i]) ++w;
    }
    return w;
}

int main(){
    init();
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; ++i){
        scanf("%s", s[i]);
    }
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            int w = getw(s[i], s[j]);
            //cout << i << " " << j << " " << w << endl;
            addedge(i, j, w);
        }
    }
    Krukal(n);
    return 0;
}