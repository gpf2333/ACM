#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e3+100;
const int inf = 0x3f3f3f3f;
char mp[maxn][maxn];
bool vis[maxn][maxn];
int dis[maxn][maxn];
int n,m;
int cnt=0;
int dir[4][2]={
    0,1,1,0,-1,0,0,-1
};
struct node{
    int x,y;
    int d;
    node(){}
    node(int x,int y,int d):x(x),y(y),d(d){}
    bool operator < (const node &n1)const{
        return d>n1.d;
    }
};
int prim(int x, int y)
{
    priority_queue<node> q;
    memset(dis,inf,sizeof(dis));
    q.push(node(x,y,0));
    int ans = 0;
    int cntt = 0;
    dis[x][y]=0;
    while(!q.empty() && cntt<cnt)
    {
        node tmp = q.top();
        q.pop();
        if(vis[tmp.x][tmp.y]) continue;
        if(mp[tmp.x][tmp.y]=='S' || mp[tmp.x][tmp.y]=='A')
        {
            ans = ans + tmp.d;
            tmp.d = 0;
            dis[tmp.x][tmp.y] = 0;
            vis[tmp.x][tmp.y] = true;
            cntt++;
        }
        for(int i=0;i<4;i++)
        {
            int nx = tmp.x + dir[i][0];
            int ny = tmp.y + dir[i][1];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(mp[nx][ny]=='#') continue;
            if(vis[nx][ny]) continue;
            if(dis[nx][ny] > tmp.d+1)
            {
                dis[nx][ny] = tmp.d+1;
                q.push(node(nx,ny,tmp.d+1));
            }
        }

    }
    return ans;
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>mp[i];
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(mp[i][j] == 'A' || mp[i][j] == 'S')
                cnt++;
        }
    }
    int flag = true;
    for(int i=0;i<n;i++)
    {
        if(flag==false)
            break;
        for(int j=0;j<m;j++)
        {
            if(flag==false)
                break;
            if(mp[i][j] == 'A' || mp[i][j] == 'S')
            {
                cout<<prim(i,j)<<endl;
                flag=false;
                break;
            }
        }
    }
}