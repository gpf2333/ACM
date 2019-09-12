#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;
const int N=100005;
int ch[N][130],n,m,sz,fl[N],ed[N],cnt,ans[N];
bool vis[N];
char s[N];
queue<int>q;

void insert(int id)
{
    int len=strlen(s),now=0;
    for (int i=0;i<len;++i)
    {
        int x=s[i];
        if (!ch[now][x])ch[now][x]=++sz;
        now=ch[now][x];
    }
    ed[now]=id;
}
void make_fail()
{
    while(!q.empty()) q.pop();
    for (int i=0;i<=128;++i)
    if (ch[0][i])q.push(ch[0][i]);
    while(!q.empty())
    {
        int now=q.front();q.pop();
        for (int i=0;i<=128;++i)
        {
            if (!ch[now][i])
            {
                ch[now][i]=ch[fl[now]][i];
                continue;
            }
            fl[ch[now][i]]=ch[fl[now]][i];
            q.push(ch[now][i]);
        }
    }
}
void ac()
{
    int len=strlen(s),now=0;
    for (int i=0;i<len;++i)
    {
        vis[now]=1;
        int x=s[i]; 
        int y=ch[now][x];
        while (y&&!vis[y])
        {
            vis[y]=1;
            if (ed[y])ans[++ans[0]]=ed[y];
            y=fl[y];
        }
        now=ch[now][x];
    }
}
int main()
{
    scanf("%d\n",&n);
    for (int i=1;i<=n;++i)
    {
        gets(s);
        insert(i);
    }
    scanf("%d\n",&m);
    make_fail();
    for (int j=1;j<=m;++j)
    {
        gets(s);
        ans[0]=0;
        memset(vis,0,sizeof(vis));
        ac();   
        if (ans[0])
        {
            printf("web %d: ",j);
            sort(ans+1,ans+ans[0]+1);
            for (int i=1;i<=ans[0];++i)
            printf("%d%c",ans[i]," \n"[i==ans[0]]);
            ++cnt;
        }
    }
    printf("total: %d\n",cnt);
}