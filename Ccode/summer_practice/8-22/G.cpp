#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 50 + 5;
const int INF = 1e5;

int n, m, h;
bool vis[maxn][maxn][maxn];
struct Node{
    int x, y, z, t;
    Node(){}
    Node(int xx, int yy, int zz, int tt):x(xx), y(yy), z(zz), t(tt){}
    bool operator < (const Node &b) const{
        return t > b.t;
    } 
};

map<pii, pii>mo;
map<pii, pii>me;
int dir[4][2] = {-1, 0, 1, 0, 0, 1, 0, -1};

int bfs(int sx, int sy, int tx, int ty){
    memset(vis, 0, sizeof(vis));
    priority_queue<Node>q;
    q.emplace(sx, sy, h, 0);
    while(!q.empty()){
        Node cur = q.top(); q.pop();
        if(cur.t > INF){
            return -1;
        }
        if(cur.x == tx && cur.y == ty){
            return cur.t;
        }
        if(vis[cur.x][cur.y][cur.z]) continue ;
        vis[cur.x][cur.y][cur.z] = 1;
        for(int i = 0; i < 4; ++i){
            int nx = cur.x + dir[i][0];
            int ny = cur.y + dir[i][1];
            if(nx <= 0 || nx > n || ny <= 0 || ny > m) continue ;
            pii tmp = make_pair(nx, ny);
            if(mo.count(tmp)){
                if(cur.z > mo[tmp].first){
                    if(vis[nx][ny][cur.z - mo[tmp].first]) continue ;
                    q.emplace(nx, ny, cur.z - mo[tmp].first, cur.t + mo[tmp].second + 1);
                }
            }else if(me.count(tmp)){
                if(!vis[nx][ny][min(cur.z + me[tmp].first, h)]){
                    q.emplace(nx, ny, min(cur.z + me[tmp].first, h), cur.t + me[tmp].second + 1);
                }
                if(!vis[nx][ny][cur.z]){
                    q.emplace(nx, ny, cur.z, cur.t + 1);
                }
            }else{
                if(!vis[nx][ny][cur.z]){
                    q.emplace(nx, ny, cur.z, cur.t + 1);
                }
            }
        }
    }
    return -1;
}

int main(){
    int c, d;
    scanf("%d%d%d%d%d", &n, &m, &h, &c, &d);
    int sx, sy, tx, ty;
    scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
    for(int i = 0; i < c; ++i){
        int x, y, z, t;
        scanf("%d%d%d%d", &x, &y, &z, &t);
        mo[make_pair(x, y)] = make_pair(z, t);
    }
    for(int i = 0; i < d; ++i){
        int x, y, z, t;
        scanf("%d%d%d%d", &x, &y, &z, &t);
        me[make_pair(x, y)] = make_pair(z, t);
    }
    printf("%d\n", bfs(sx, sy, tx, ty));
}