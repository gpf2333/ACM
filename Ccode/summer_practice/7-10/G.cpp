#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
const int INF = 0x3f3f3f3f;
int n, m;
char s[maxn][maxn];
int dis[maxn][maxn];
int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
struct Node{
    int x, y, d;
    Node(){};
    Node(int xx, int yy, int dd): x(xx), y(yy), d(dd){};
    bool operator < (const Node &b) const {
        return d > b.d;
    }
};

int prim(int x, int y, const int cnt){
    memset(dis, INF, sizeof(dis));
    priority_queue<Node>q;
    q.emplace(x, y, 0);
    int ans = 0, num = 0;
    while(!q.empty()){
        Node cur = q.top(); q.pop();
        if(!dis[cur.x][cur.y]) continue ;
        if(s[cur.x][cur.y] == 'S' || s[cur.x][cur.y] == 'A'){
            ans += cur.d;
            if(++num >= cnt) return ans;
            cur.d = 0;
            dis[cur.x][cur.y] = 0;
        }
        for(int i = 0; i < 4; ++i){
            int nx = cur.x + dir[i][0];
            int ny = cur.y + dir[i][1];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue ;
            if(s[nx][ny] == '#' || !dis[nx][ny]) continue ;
            if(dis[nx][ny] > cur.d + 1){
                dis[nx][ny] = cur.d + 1;
                q.emplace(nx, ny, cur.d + 1);
            }
        }
    }
    return ans;
}

int main(){
    while(~scanf("%d%d",&n,&m)){
        for(int i = 0; i < n; ++i){
            scanf("%s", s[i]);
        }
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(s[i][j] == 'S' || s[i][j] == 'A'){
                    ++cnt;
                }
            }
        }
        bool ok = false;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(s[i][j] == 'S' || s[i][j] == 'A'){
                    printf("%d\n", prim(i, j, cnt));
                    ok = true;
                    break ;
                }
            }
            if(ok) break ;
        }
    }
    return 0;
}