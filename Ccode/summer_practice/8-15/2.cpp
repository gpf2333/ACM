#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>

const int Times=10;
const int N=100005;
const int mod = 1e9 + 7;
using namespace std;
typedef long long LL;

LL ct,cnt;
LL fac[N],num[N],p[N],arr[N][2];
LL tx[N],ty[N];

LL gcd(LL a,LL b)
{
    return b? gcd(b,a%b):a;
}

LL multi(LL a,LL b,LL m)
{
    LL ans=0;
    while(b)
    {
        if(b&1)
        {
            ans=(ans+a)%m;
            b--;
        }
        b>>=1;
        a=(a+a)%m;
    }
    return ans;
}

LL quick_mod(LL a,LL b,LL m)
{
    LL ans=1;
    a%=m;
    while(b)
    {
        if(b&1)
        {
            ans=multi(ans,a,m);
            b--;
        }
        b>>=1;
        a=multi(a,a,m);
    }
    return ans;
}

bool Miller_Rabin(LL n)
{
    if(n==2) return true;
    if(n<2||!(n&1)) return false;
    LL a,m=n-1,x,y;
    int k=0;
    while((m&1)==0)
    {
        k++;
        m>>=1;
    }
    for(int i=0; i<Times; i++)
    {
        a=rand()%(n-1)+1;
        x=quick_mod(a,m,n);
        for(int j=0; j<k; j++)
        {
            y=multi(x,x,n);
            if(y==1&&x!=1&&x!=n-1) return false;
            x=y;
        }
        if(y!=1) return false;
    }
    return true;
}

LL Pollard_rho(LL n,LL c)
{
    LL x,y,d,i=1,k=2;
    y=x=rand()%(n-1)+1;
    while(true)
    {
        i++;
        x=(multi(x,x,n)+c)%n;
        d=gcd((y-x+n)%n,n);
        if(1<d&&d<n) return d;
        if(y==x) return n;
        if(i==k)
        {
            y=x;
            k<<=1;
        }
    }
}

void find(LL n,int c)
{
    if(n==1) return;
    if(Miller_Rabin(n))
    {
        fac[ct++]=n;
        return ;
    }
    LL p=n;
    LL k=c;
    while(p>=n) p=Pollard_rho(p,c--);
    find(p,k);
    find(n/p,k);
}

struct T
{
    LL p,d;
};

LL w;

T multi_er(T a,T b,LL m)
{
    T ans;
    ans.p=((multi(a.p,b.p,m)+multi(multi(a.d,b.d,m),w,m)))%m;
    ans.d=(multi(a.p,b.d,m)+multi(a.d,b.p,m))%m;
    return ans;
}

T power(T a,LL b,LL m)
{
    T ans;
    ans.p=1;
    ans.d=0;
    while(b)
    {
        if(b&1)
        {
            ans=multi_er(ans,a,m);
            b--;
        }
        b>>=1;
        a=multi_er(a,a,m);
    }
    return ans;
}

LL TX[N],TY[N];

void Sort(LL tx[],LL ty[],int r)
{
    for(int i=0; i<r-1; i++)
    {
        for(int j=0; j<r-i-1; j++)
        {
            if(tx[j]>tx[j+1])
            {
                LL tmp2=tx[j];
                tx[j]=tx[j+1];
                tx[j+1]=tmp2;
                LL tmp3=ty[j];
                ty[j]=ty[j+1];
                ty[j+1]=tmp3;
            }
        }
    }
}

int main()
{
    
    LL n,ans,px,qx,t,tmp,a;
    LL b, c;
    int tt;
    scanf("%d", &tt);
    while(tt--)
    {
        scanf("%lld%lld",&b, &c);
        LL ta = (b % mod) * (b % mod) % mod;
        n = (ta - 2LL * c % mod) % mod;
        n = (n + mod) % mod;
        if(n == 1)
        {
            puts("0 1");
            continue;
        }
        ct=0;
        find(n,120);
        sort(fac,fac+ct);
        for(int i=0; i<ct; i++)
            p[i]=fac[i];
        num[0]=1;
        int k=1;
        for(int i=1; i<ct; i++)
        {
            if(fac[i]==fac[i-1])
                ++num[k-1];
            else
            {
                num[k]=1;
                fac[k++]=fac[i];
            }
        }
        cnt=k;
        bool flag=true;
        for(int i=0; i<cnt; i++)
        {
            if(fac[i]%4==3&&num[i]%2==1)
            {
                flag=false;
                break;
            }
        }
        if(!flag)
        {
            puts("-1 -1");
            continue;
        }
        int C=0;
        int r=0;
        while(r<ct)
        {
            if(p[r]==2)
            {
                LL digit=0;
                for(int kk=r; kk<ct; kk++)
                {
                    if(p[kk]==p[kk+1])
                        digit++;
                    else break;
                }
                digit++;
                LL tmp1=1;
                for(int kk=0; kk<digit/2; kk++)
                    tmp1*=p[r];
                if(digit%2==1)
                {
                    arr[C][0]=tmp1;
                    arr[C][1]=tmp1;
                }
                else
                {
                    arr[C][0]=0;
                    arr[C][1]=tmp1;
                }
                C++;
                r+=digit;
                continue;
            }
            if(p[r]%4==3)
            {
                LL digit=0;
                for(int kk=r; kk<ct; kk++)
                {
                    if(p[kk]==p[kk+1])
                        digit++;
                    else break;
                }
                digit++;
                LL tmp1=1;
                for(int kk=0; kk<digit/2; kk++)
                    tmp1*=p[r];
                arr[C][0]=0;
                arr[C][1]=tmp1;
                C++;
                r+=digit;
                continue;
            }
            tmp=(LL)sqrt(p[r]*1.0);
            while(1)
            {
                a=rand()%tmp;
                w=a*a+1;
                t=quick_mod(w,(p[r]-1)/2,p[r]);
                if((t+1)%p[r]==0) break;
            }
            T tmp1;
            tmp1.p=a;
            tmp1.d=1;
            T ans=power(tmp1,(p[r]+1)/2,p[r]);
            LL px=ans.p;
            if(px>p[r]-px) px=p[r]-px;
            LL rr=p[r]%px,tt=p[r];
            LL tmp0=(LL)sqrt(tt);
            while(rr>=tmp0)
            {
                p[r]=px;
                px=rr;
                rr=p[r]%px;
            }
            LL ret=(LL)sqrt(tt-rr*rr);
            if(rr>ret) swap(rr,ret);
            arr[C][0]=rr;
            arr[C][1]=ret;
            C++;
            r++;
        }
        LL s;
        LL cnt1=0;
        TX[cnt1]=arr[0][0];
        TY[cnt1]=arr[0][1];
        cnt1++;
        for(int i=1; i<C; i++)
        {
            for(int k=0; k<cnt1; k++)
            {
                tx[k]=TX[k];
                ty[k]=TY[k];
            }
            s=0;
            for(int k=0; k<cnt1; k++)
            {
                LL t1=tx[k]*arr[i][0]+ty[k]*arr[i][1];
                LL t2=tx[k]*arr[i][1]-ty[k]*arr[i][0];
                if(t1<0) t1=-t1;
                if(t2<0) t2=-t2;
                if(t1>t2) swap(t1,t2);

                LL t3=tx[k]*arr[i][0]-ty[k]*arr[i][1];
                LL t4=tx[k]*arr[i][1]+ty[k]*arr[i][0];
                if(t3<0) t3=-t3;
                if(t4<0) t4=-t4;
                if(t3>t4) swap(t3,t4);

                TX[s]=t1;
                TY[s]=t2;
                s++;
                TX[s]=t3;
                TY[s]=t4;
                s++;
            }
            Sort(TX,TY,s);
            int k=1;
            for(int j=1; j<s; j++)
            {
                if(TX[j]!=TX[j-1])
                {
                    TX[k]=TX[j];
                    TY[k]=TY[j];
                    k++;
                }
            }
            cnt1=k;
        }
        bool ok = false ;
        for(int i=0; i<cnt1; i++){
            LL tb = (TX[i] + TY[i]) % mod;
            LL tc = ((LL)TX[i] * TY[i] % mod);
            if(tb == b && tc == c){
                ok = true;
                printf("%lld %lld\n", TX[i], TY[i]); 
                break ;
            }
            // cout<<TX[i]<<" "<<TY[i]<<endl;
        }
        if(!ok){
            puts("-1 - 1");
        }  
    }
    return 0;
}