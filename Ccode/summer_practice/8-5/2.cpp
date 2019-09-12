#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e4 + 330;
int vec[maxn][10];
vector<int> ans;
int last, p[maxn];
ll fac[25];
void init(){
    fac[0] = 1;
    for(int i = 1; i <= 10; i++)
    {
        fac[i] = fac[i - 1] * i;
    }
}

bool cmp(const int &a, const int &b){
    int *v1 = vec[a], *v2 = vec[b];
    if(last != -1 && v1[1] - last != v2[1] - last){
        return v1[1] - last < v2[1] - last;
    } 
    for(int i = 2; i <= v1[0]; i++){
        if(v1[i] - v1[i - 1] != v2[i] - v2[i - 1]){
            return v1[i] - v1[i - 1] < v2[i] - v2[i - 1];
        }
    }
    return false;
}

int main(){
    int T;
    init();
    scanf("%d", &T);
    while(T--){
        int n, k;
        scanf("%d%d", &n, &k);
        ans.clear();
        int pos = 0;
        int a[10];
        for(int i = 1; i <= 8; i++)
        {
            if(fac[i] > k){
                pos = i;
                break;
            }
        }
        if(n <= 8){
            for(int i = 1; i <= n; i++){
                a[i] = i;
            }
            last = - 1;
            int cnt = 0; p[cnt] = 0;
            do{
                vec[++cnt][0] = n;
                p[cnt] = cnt;
                for(int i = 1; i <= n; i++){
                    vec[cnt][i] = a[i];
                }
            }while(next_permutation(a + 1, a + 1 + n));
            sort(p + 1 , p + 1 + cnt, cmp);
            for(int i = 1; i <= vec[p[k]][0]; ++i){
                ans.push_back(vec[p[k]][i]);
            }
        }
        else if(n >= 9){
            ans.push_back(n);
            for(int i = 1; i <= n - 1 - pos; i++){
                ans.push_back(i);
            }
            for(int i = n - pos; i <= n - 1; i++){
                a[i - n + pos + 1] = i;
            }
            p[0] = 0;
            last = n - 1 - pos;
            int cnt = 0;
            do{
                vec[++cnt][0] = pos;
                p[cnt] = cnt;
                for(int i = 1; i <= pos; i++){
                    vec[cnt][i] = a[i];
                }
            }while(next_permutation(a + 1, a + 1 + (pos)));
            sort(p + 1 , p + 1 + cnt, cmp);
            for(int i = 1; i <= vec[p[k]][0]; ++i){
                ans.push_back(vec[p[k]][i]);
            }
        }
        printf("%d", ans[0]);
        for(int i = 1; i < (int)ans.size(); ++i){
            printf(" %d", ans[i]);
        }
        puts("");
    }
}