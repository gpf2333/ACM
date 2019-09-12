#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull; 
const int maxn = 6;
struct Node{
    int id;
    int x, y;
    int val[maxn][maxn];
    int d;
};

int dir[4][2] = {-1, -1, -1, 0, 1, 0, 1, 1};
map<ull, int>vis[2];
ull get(const Node &a){
    ull res = 0;
    for(int i = 0; i < maxn; ++i){
        for(int j = 0; j <= i; ++j){
            res = res * 6 + a.val[i][j];
        }
    }
    return res;
}

int bfs(Node &s, Node &e){
    queue<Node>q;
    vis[0].clear(); vis[1].clear();
    s.id = 0, e.id = 1;
    s.d = e.d = 0;
    vis[0][get(s)] = 0, vis[1][get(e)] = 0;
    q.push(s); q.push(e);
    while(!q.empty()){
        Node cur = q.front(); q.pop();
        ull res = get(cur);
        if(vis[cur.id ^ 1].count(res) && vis[cur.id ^ 1][res] + cur.d <= 20){
                return vis[cur.id ^ 1][res] + cur.d;
        }
        if(cur.d >= 10) continue ;
        for(int i = 0; i < 4; ++i){
            Node nex = cur;
            nex.x = cur.x + dir[i][0];
            nex.y = cur.y + dir[i][1];
            if(nex.y > nex.x || nex.x < 0 || nex.x >= 6 || nex.y < 0 || nex.y >= 6) continue ;
            swap(nex.val[cur.x][cur.y], nex.val[nex.x][nex.y]);
            res = get(nex);
            if(vis[nex.id].count(res)) continue ;
            vis[nex.id][res] = ++nex.d;
            q.push(nex);
        }
    }
    return -1;
}

int main(){
    Node s, e;
    int T;
    scanf("%d",&T);
    while(T--){
        e.x = e.y = 0;
        for(int i = 0; i < maxn; ++i){
            for(int j = 0; j <= i; ++j){
                scanf("%d", &s.val[i][j]);
                if(!s.val[i][j]) s.x = i, s.y = j;
                e.val[i][j] = i;
            }
        }
        int ans = bfs(s, e);
        if(~ans){
            printf("%d\n", ans);
        }else{
            puts("too difficult");
        }
    }
    return 0;
}