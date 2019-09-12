#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+100;
vector<int>pos;
vector<int>v[maxn];
ll ans[maxn];
int sizz[maxn];
ll anss;
bool vis[maxn];
int n,n1;
bool cmp(int x,int y)
{
	return  ans[x]<ans[y];
 } 
int dfs1(int x,int y,int dep,int root)
{
	vis[x]=1;
	sizz[x]=1;
	pos.push_back(x);
	for (int i=0;i<v[x].size();i++)
	{
		int b=v[x][i];
		if (b==y) continue;
		sizz[x]+=dfs1(b,x,dep+1,root);
		ans[root]+=dep+1;
	}
	return sizz[x];
}
void dfs2(int x,int y,int root)
{
	for (int i=0;i<v[x].size();i++)
	{
		int b=v[x][i];
		if (b==y) continue;
	    ans[b]=ans[x]-sizz[b]+(n1-sizz[b]);
	    dfs2(b,x,root);
	} 
}
void dfs3(int x,int y)
{
	for (int i=0;i<v[x].size();i++)
	{
		int b=v[x][i];
		if (b==y) continue;
		dfs3(b,x);
		anss+=1ll*sizz[b]*(n-sizz[b]);
	} 
}
int main()
{
    int a1,a2,p1,p2,i;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	v[i].clear();
	for (i=1;i<n-1;i++)
	{
		scanf("%d %d",&a1,&a2);
		v[a1].push_back(a2);
		v[a2].push_back(a1);
	}
	
	p1=0;p2=0;
	memset(vis,0,sizeof(vis));
	for (i=1;i<=n;i++)
	{
		if (!vis[i])
		{
			dfs1(i,i,0,i);
			n1=pos.size();
			dfs2(i,i,i);
			sort(pos.begin(),pos.end(),cmp);
			if (p1==0) p1=pos[0]; else p2=pos[0];
			pos.clear();
		}
	}
	v[p1].push_back(p2);
	v[p2].push_back(p1);
    cout << p1 << " " << p2 << endl;
	dfs1(1,1,0,0);
	dfs3(1,1);
    for(int i = 1; i <= n; ++i){
        cout << sizz[i] << " ";
    }
    cout << endl;
	cout<<anss<<endl;
	return 0;
 } 
 /*
 7
1 2
1 3
2 4
5 6
5 7
*/