/*
�ڵ��1��ʼ�ĺ�׺�Զ���ģ��
tΪ0���ʾ��ͬλ�õ���ͬ�Ӵ�����һ��,tΪ1���ʾ��ͬλ�õ���ͬ�Ӵ��������
k��ʾ����ֵ����kС���Ӵ���
*/
const int maxn = 5e5 + 10;
const int mx = 26; //�ַ�����С
struct SAM{
    int ch[maxn << 1][mx], len[maxn << 1], link[maxn << 1];
    int sz, last;
    int num[maxn << 1];  //num[i]���Ӵ������ڵ�i
    int siz[maxn << 1];  //siz[i]��ʾi�������Endpos�ļ��ϴ�С��Ҳ����i����Ӧ�ַ������ϵĳ��ִ���
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
    int tak[maxn], rk[maxn << 1]; //����lenͰ����֮��Ҳ����Parent����BFS��/�Զ�����������
    //���԰�������SA��Ͱ���򷽷��������½�Parent����Ҷ�ӵ���/�Զ�������������rk[1]... rk[sz]��ʾ����
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