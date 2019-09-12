#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll; 
const int N = 1e5 + 10;
struct node
{
	int x,y,next;
    int c;
}a[N * 2];

int tot,head[N];

int f[N][3], g[N][3];
int t[N][2];
bool vis[N];

int n;

void ins(int x,int y, int c)
{
	tot++;
	a[tot].x=x;
    a[tot].y=y;
    a[tot].c=c;
	a[tot].next=head[x];
    head[x]=tot;
}

void dp(int x,int fa)
{
	for(int k=head[x];k;k=a[k].next)
	{
		int y=a[k].y; if(y==fa) continue;
		dp(y,x);
		if(f[x][0] < f[y][0] + a[k].c)
		{
			t[x][0] = y;
			f[x][1] = f[x][0];
            if(vis[x]) g[x][1] = f[x][0];
			f[x][0] = f[y][0] + a[k].c;
            if(vis[x]) g[x][0] = f[x][0];
		}
		else if(f[x][1] < f[y][0] + a[k].c)
		{
			f[x][1] = f[y][0] + a[k].c;
            if(vis[x]) g[x][1] = f[x][1];
			t[x][1] = y;	
		}
	}
}

void dfs(int x,int fa)
{
	for(int k = head[x]; k; k=a[k].next)
	{
		int y = a[k].y; 
        if(y == fa) continue;
		if(t[x][0] != y){
            f[y][2] = max(f[x][0],f[x][2]) + a[k].c;
            if(vis[x]){
                g[x][2] = max(g[x][0], g[x][2]) + a[k].c;
            }
        }
		else{
            f[y][2] = max(f[x][1],f[x][2]) + a[k].c;
            if(vis[x]){
                g[x][2] = max(g[x][1], g[x][2]) + a[k].c;
            }
        } 
		dfs(y,x);
	}
}

int main()
{
    int k;
	while(~scanf("%d%d", &n, &k))
	{
		memset(head,0,sizeof(head)); 
        tot = 0;
        vis[0] = vis[1] = 0;
		for(int x = 2; x <=n; x++)
		{
			int u, v;
            scanf("%d%d",&u, &v);
			ins(u,v,1); ins(v, u, 1); 
            vis[x] = 0;
		}
        for(int i = 0; i < k; ++i){
            int x;
            scanf("%d", &x);
            vis[x] = 1;
        }
		memset(f,0,sizeof(f));
		memset(t,0,sizeof(t));
        memset(g, 0, sizeof(g));
		dp(1,0); 
		f[1][2] = f[1][1];
        g[1][2] = g[1][1]; 
        dfs(1,0);
		// for(int i=1; i <= n; i++)
		// {
		// 	printf("%lld\n",max(f[i][0],f[i][2]));	
		// }
        int ans = 0;
        for(int i = 1; i <= n; ++i){
            ans = max(g[i][0], g[i][2]);
        }
        printf("%d\n", ans);
	}
	return 0;
}
