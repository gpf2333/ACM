// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

struct node{
    int link; //link后缀链接所指向的自己的后缀
    int len; //len当前中点等价类中长度最长的哪一个的长度
    bool cl; //是否是复制的
    int nxt[26]; //后缀自动机（DAG）所指向的 
}st[N << 1];    //后缀自动机兼后缀链接 
int siz;    //siz一共的节点数 
int last;   //last上一次加入的状态

void sa_init(){ //初始化 
    siz = 1, last = 0;
    st[0].len = 0;
    st[0].link = -1;
    /*若关于不同的字符串多次建立后缀自动机，就需要执行这些代码：
    for (int i=0; i<MAXLEN*2; ++i)
        st[i].next.clear();*/
}

void sa_extend(int c){
    //令last为对应整个字符串的状态（最初last=0，在每次字符添加操作后我们都会改变last的值） 
    int cur = siz++; int p;
    st[cur].len = st[last].len + 1;
    //建立一个新的状态cur，令len(cur) = len(last)+1，而link(cur)的值并不确定
    for(p = last; p != -1 && !st[p].nxt[c]; p = st[p].link)
        st[p].nxt[c] = cur;
    //将之前子串的后缀都加上当前字符（ 添加字符c的转移） 
    //我们最初在last，如果它没有字符c的转移，那就添加字符c的转移，指向cur，
    //然后走向其后缀链接，再次检查——如果没有字符c的转移，就添加上去
    //如果在某个节点已有字符c的转移，就停止，并且令p为这个状态的编号
    //如果“某节点已有字符c的转移”这一事件从未发生，而我们来到了空状态-1（经由t_0的后缀指针前来）
    //我们简单地令link(cur)=0，跳出
    if(p == -1) st[cur].link = 0;
    else{
        //假设我们停在了某一状态q，是从某一个状态p经字符c的转移而来
        //现在有两种情况：len(p)+1=len(q)或不然
        int q = st[p].nxt[c];
        //如果len(p)+1=len(q)，那么我们简单地令link(cur)=q，跳出
        if(st[q].len == st[p].len + 1)  st[cur].link = q;
        //p是last的后缀   如果q只比p多了一个字符（当前字符c）
        //说明q是cur的后缀，于是就连一条边 
        else{
            //否则，情况就变得更加复杂。必须新建一个q的“拷贝”状态：
            //建立一个新的状态clone，将q的数据拷贝给它（后缀链接，以及转移）
            //除了len的值：需要令len(clone) = len(p) + 1
            int clone = siz++;
            st[clone].cl = true;
            st[clone].link = st[q].link;
            for(int i = 0; i < 26; i++) st[clone].nxt[i] = st[q].nxt[i]; //memcpy要挂 
            st[clone].len = st[p].len + 1;
            for(; p!=-1 && st[p].nxt[c] == q; p = st[p].link)
                st[p].nxt[c] = clone;
            //最终，我们需要做的最后一件事情就是——从p开始沿着后缀链接走，
            //对每个状态我们都检查是否有指向q的，字符c的转移，
            //如果有就将其重定向至clone（如果没有，就终止循环）
            st[q].link = st[cur].link = clone;
            //在拷贝之后，我们将cur的后缀链接指向clone，并将q的后缀链接重定向到clone
        }
    }
    last = cur;
    //在任何情况下，无论在何处终止了这次添加操作
    //我们最后都将更新last的值，将其赋值为cur
}
//如果我们还需要知道哪些节点是终止节点而哪些不是，我们可以在构建整个字符串的后缀自动机之后找出所有终止节点。
//对此我们考虑对应整个字符串的节点（显然，就是我们储存在变量last中的节点），
//我们沿着它的后缀链接走，直到到达初始状态，并且将途径的每个节点标记为终止节点。
//很好理解，如此我们标记了字符串s所有后缀的对应状态，也就是我们想要找出的终止状态。

char s[N];
long long ans;
struct edge{
    int v, nxt;
}e[N<<1];
int first[N << 1], cnt=0;

void add(int u,int v){
    e[++cnt].v = v;
    e[cnt].nxt = first[u]; first[u] = cnt;
}

int f[N<<1];
void dfs(int x){
    for(int i = first[x]; i; i = e[i].nxt){
        dfs(e[i].v);
        f[x] += f[e[i].v];
    }
    if(!st[x].cl) f[x]++;
    if(f[x] > 1)ans = max(ans, (long long)f[x]*st[x].len);
}

int main(){
    scanf("%s",s+1);
    sa_init();
    int le=strlen(s+1); //太慢，记录一下 
    for(int i=1;i<=le;i++)
        sa_extend((int)(s[i]-'a'));
    for(int i=1;i<siz;i++)
    	add(st[i].link,i);
    dfs(0);
    printf("%lld",ans);
    return 0;
}
