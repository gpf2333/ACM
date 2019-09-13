/*
节点从1开始的后缀自动机模板
t为0则表示不同位置的相同子串算作一个,t为1则表示不同位置的相同子串算作多个
k表示输出字典序第k小的子串。
*/
const int maxn = 5e5 + 10;
const int mx = 26; //字符集大小
struct SAM{
    int ch[maxn << 1][mx], len[maxn << 1], link[maxn << 1];
    int sz, last;
    int num[maxn << 1];  //num[i]个子串进过节点i
    int siz[maxn << 1];  //siz[i]表示i所代表的Endpos的集合大小，也就是i所对应字符串集合的出现次数
    inline void init(){
        sz = 1, last = 1;
        len[1] = link[1] = 0;
        for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
    }
    void add(int c){
        c -= 'a';
        int p, np = ++sz;
        for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
        len[np] = len[last] + 1;
        siz[np] = 1;

        for(p = last; p && !ch[p][c]; p = link[p]){
            ch[p][c] = np;
        }
        if(!p){
            link[np] = 1;
        }else{
            int q = ch[p][c];
            if(len[q] == len[p] + 1){
                link[np] = q;
            }else{
                int nq = ++sz;
                for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
                len[nq] = len[p] + 1;
                siz[nq] = 0;
                for(int i = 0; i < mx; ++i){
                    ch[nq][i] = ch[q][i];
                }
                for(; p && ch[p][c] == q; p = link[p]){
                    ch[p][c] = nq;
                }
                link[nq] = link[q];
                link[q] = link[np] = nq;
            }
        }
        last = np;
    }
    int tak[maxn], rk[maxn << 1]; //按照len桶排序之后也就是Parent树的BFS序/自动机的拓扑序
    //所以按照类似SA的桶排序方法可以如下将Parent树从叶子到根/自动机反拓扑序用rk[1]... rk[sz]表示出现
    void count(int T){
        memset(tak, 0, sizeof(tak));
        for(int i = 1; i <= sz; ++i){
            ++tak[len[i]];
        }
        for(int i = 1; i <= sz; ++i){
            tak[i] += tak[i - 1];
        }
        for(int i = 1; i <= sz; ++i){
            rk[tak[len[i]]--] = i;
        }

        for(int i = sz; i; --i){
            if(T){
                siz[link[rk[i]]] += siz[rk[i]];
            }else{
                siz[rk[i]] = 1;
            }
        }

        siz[1] = 0;
        for(int i = sz; i; --i){
            num[rk[i]] = siz[rk[i]];
            for(int j = 0; j < mx; ++j){
                if(ch[rk[i]][j] == 0) continue ;
                num[rk[i]] += num[ch[rk[i]][j]];
            }
        }
    }

    void solve(int k){
        if(k > num[1]){
            puts("-1"); return ;
        }
        int cur = 1;
        k -= siz[1];
        num[1] = 0;
        while(k > 0){
            int c = 0;
            while(k > num[ch[cur][c]]){
                k -= num[ch[cur][c]];
                ++c;
            }
            cur = ch[cur][c];
            putchar('a' + c);
            k -= siz[cur];
        }
        puts("");
    }
}sam;