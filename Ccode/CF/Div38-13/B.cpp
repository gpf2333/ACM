#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 400 + 100;
int a[maxn];
vector<int>vec;
int cnt[10040];

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, x;
        scanf("%d", &n);
        int up = n * 4;
        vec.clear();
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= up; ++i){
            scanf("%d", &x);
            vec.push_back(x);
            ++cnt[x];
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());        
        bool flag = 1;
        if((int)vec.size() == 1){
            flag = cnt[vec[0]] % 4 ? 0 : 1;
        }else{
            int areas = vec[0] * vec[(int)vec.size() - 1];
            for(int i = 0, j = vec.size() - 1; i <= j; ++i, --j){
                if(i != j){
                    if(cnt[vec[i]] % 2 != 0 && cnt[vec[j]] % 2 != 0){
                        flag = 0; break ;
                    }
                    if(cnt[vec[i]] != cnt[vec[j]]){
                        flag = 0; break ;
                    }
                    int tmp = vec[i] * vec[j];
                    if(tmp != areas){
                        flag = 0; break ;
                    }
                }else{
                    if(cnt[vec[i]] % 4 != 0){
                        flag = 0; break ;
                    }
                    int tmp = vec[i] * vec[j];
                    if(tmp != areas){
                        flag = 0; break ;
                    }
                }
            }
        }
        if(flag){
            puts("YES");
        }else{
            puts("NO");
        }
    }
}