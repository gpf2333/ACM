#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
struct FastIO
{
    static const int S = 2*100;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar()
    {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos==len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos==len) exit(0);
        return buf[pos ++];
    }
    inline int xint()
    {
        int s = 1, c = xchar(), x = 0;
        while(c<=32) c = xchar();
        if(c=='-') s = -1, c = xchar();
        for(;'0'<=c && c<='9';c=xchar()) x = x*10+c-'0';
        return x * s;
    }
    ~FastIO()
    {
        if(wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
}io;

struct node{
    int v,next;
    node(){}
    node(int v,int next):v(v),next(next){}
}edge[maxn<<1];
int head[maxn],tot;
struct Node{
    int u;
    int d;
    Node(){}
    Node(int u, int d):u(u),d(d){}
};
inline void addedge(int u,int v)
{
    edge[tot] = node(v,head[u]);
    head[u] = tot++;
}
bool vis[maxn];
int in[maxn];
int n,k;
void init(int n)
{
    for(int i=0;i<=n;i++)
    {
        head[i]=-1;
        in[i]=vis[i]=0;
    }
    tot = 0;
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(0);
    int t;
    t = io.xint();
    while(t--)
    {
        n = io.xint();
        k = io.xint();
        init(n);
        for(int i=2;i<=n;i++)
        {
            int u;
            u = io.xint();
            addedge(u, i);
            addedge(i, u);
            in[u]++;
            in[i]++;
        }
        int cnt = 0;//叶子结点
        int sum = 0;//
        queue<int> q;
        for(int i=1;i<=n;i++)
        {
            if(in[i]==1) q.push(i);
            //vis[i]=true;
        }
        while(!q.empty())
        {
            int tmp = q.front();
            q.pop();
            for(int i = head[tmp]; ~i ; i =edge[i].next)
            {
                int to = edge[i].v;
                //if(vis[to]) continue;
                if(!vis[to] && !vis[tmp])
                {
                    vis[to] = true;
                    vis[tmp] = true;
                    cnt++;
                }
                in[to]--;
                if(in[to]==1)
                    q.push(to);
            }


        }
        sum = n - cnt * 2;
        //cout<<cnt<<endl;
        int ans = 0;
        if(k%2==0)
        {
            if(cnt*2>=k)
                ans = k/2;
            else
            {
                ans = cnt+k-cnt*2;
            }
        }
        else
        {
            if(cnt*2>k)
                ans = k/2 + 1;
            else
            {
                ans = cnt + k - cnt * 2;
            }
        }
        printf("%d\n",ans);
    }

}