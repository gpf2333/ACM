#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
char mp[maxn][maxn];
int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};
int n,m;
int cnt;
const int INF = 0x3f3f3f3f;
bool outside(int x,int y)
{
    return x < 1 || x > n || y < 1 || y > m;
}
 
struct node
{
    int x,y,s;
    bool operator < (const node &p) const
    {
        return s > p.s;
    }
};
 
priority_queue<node>q;
 
int vis[maxn][maxn];
int bfs()
{
    int ans = 0,num = 0;
    while(!q.empty())
    {
        node cur = q.top();
        q.pop();
        if(!vis[cur.x][cur.y]) continue;
        if(mp[cur.x][cur.y] == 'A' || mp[cur.x][cur.y] == 'S')
        {
            ans += cur.s;
            if(++num >= cnt) return ans;
                cur.s = 0;
                vis[cur.x][cur.y] = 0;
        }
        for(int i = 0;i < 4; i++)
        {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if(outside(nx,ny)) continue;
            if(!vis[nx][ny] || mp[nx][ny] == '#')  continue;
            if(vis[nx][ny] > cur.s + 1)
            {
                vis[nx][ny] = cur.s + 1;
                q.push(node{nx,ny,cur.s + 1});
            }
        }
    }
    return ans;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cnt = 0;
    cin >> n >> m;
    int sx,sy;
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= m; j++)
        {
            cin >> mp[i][j];
            if(mp[i][j] == 'A' || mp[i][j] == 'S') {sx = i;sy = j;cnt++;}
        }
    memset(vis, INF, sizeof(vis));
    q.push(node{sx,sy,0});
    cout << bfs() << endl;
    return 0;
}