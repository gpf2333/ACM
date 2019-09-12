#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 100;
typedef long long ll;
struct PAM{//回文树
    int next[maxn][26],fail[maxn],len[maxn],cnt[maxn],S[maxn];
    int id,n,last;
    int newnode(int x){
        for(int i=0;i<26;i++){
            next[id][i]=0;
        }
        cnt[id]=0;
        len[id]=x;
        return id++;
    }
    void init(){
        id=0;
        newnode(0);
        newnode(-1);
        fail[0]=1;
        S[0]=-1;
        last=n=0;
    }
    int getfail(int x){
        while(S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    void Insert(int c){
        S[++n]=c;
        int cur=getfail(last);
        if(!next[cur][c]){
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            next[cur][c]=now;
        }
        last=next[cur][c];
        cnt[last]++;
    }
 
}pam;
 
 
char str[maxn];
 
int wa[maxn],wb[maxn],wv[maxn];
int c[maxn];
int cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b] && r[a+l]==r[b+l];
}
 
void cal_the_houzhui(char *r,int *sa,int n,int m)
{
    int i,j,p;
    int *x=wa,*y=wb;
 
    //先直接对每个后缀的第一个字符进行基数排序
    for(i=0;i<m;i++)
        c[i]=0;
 
    for(i=0;i<n;i++)
        c[x[i]=r[i]]++;
    for(i=1;i<m;i++)
        c[i]+=c[i-1];
    for(i=n-1;i>=0;i--)
        sa[--c[x[i]]]=i;
 
    //然后进行log级的基数排序，使得sa数组稳定
    p=1;
    for(j=1;p<n;j*=2,m=p)
    {
        //对第二维进行基数排序
        //可以直接利用sa数组进行排序
        //y[p]表示的在二维排序中，第P小的第一位在什么位置
        for(p=0,i=n-j;i<n;i++)
            y[p++]=i;//这里从n-j~n-1的是不可能有第二维的，因为第二维已经超出了n-1
                        //所以在第二维的排序中，他们是最小的，当然就是排在最前面的
        for(i=0;i<n;i++)
            if(sa[i]>=j)
                y[p++]=sa[i]-j;
        for(i=0;i<n;i++)//根据y数组来重新定义wv
            wv[i]=x[y[i]];
 
        for(i=0;i<m;i++)
            c[i]=0;
        for(i=0;i<n;i++)
            c[wv[i]]++;
        for(i=1;i<m;i++)
            c[i]+=c[i-1];
        for(i=n-1;i>=0;i--)
            sa[--c[wv[i]]] = y[i];
        swap(x,y);
        p=1;
        x[sa[0]] = 0;
        for(i=1;i<n;i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
 
}
 
int rk[maxn],height[maxn];
void cal_the_height(char *r,int *sa,int n)
{
    int i,j,k=0;
    //通过sa求出rank
    for(i=0;i<n;i++)
        rk[sa[i]]=i;
    for(i=0;i<n;height[rk[i++]]=k)
    {
        for(k?k--:0,j=sa[rk[i]-1];r[i+k]==r[j+k];)
            k++;
    }
}
 
int n;
int _sa[maxn];
 
ll solve()
{
    cal_the_houzhui(str,_sa,n+1,256);
    cal_the_height(str,_sa,n+1);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=n-_sa[i]-height[i];
    }
    return ans;
}
 
int main()
{
    scanf("%s",str);
    int lenn = strlen(str);
    pam.init();
    for(int i = 0;i < lenn; i++)
    {
        pam.Insert(str[i]-'a');
    }
    str[lenn] = '$';
    int lennn = lenn;
    for(int i = lenn - 1; i >= 0; i--)
    {
        str[++lennn] = str[i];
    }
    str[++lennn] = '\0';
    n = lennn;
    printf("%lld\n",(solve() - ll(lenn + 1)*(lenn + 1) + (ll)pam.id - 2)/2LL);
    return 0;
}