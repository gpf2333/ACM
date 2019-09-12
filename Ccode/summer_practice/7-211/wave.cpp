#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
vector<int>vec[105];
int a[maxn], tmp[maxn];
map<int,int>mp;
int main(){
    int n, c;
    while(~scanf("%d%d", &n, &c)){
        for(int i = 0; i <= c; ++i) vec[i].clear();
        mp.clear();
        int cnt = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            if(!mp.count(a[i])) mp[a[i]] = cnt++;
        }
        for(int i = 1; i <= n; ++i){
            vec[mp[a[i]]].push_back(i);
        }
        int ans = 0;
        int len = 0;
        for(int i = 0; i < c; ++i){
            for(int j = i + 1; j < c; ++j){
                int p = 0, q = 0;
                len = 0; 
                while(p < vec[i].size() || q < vec[j].size()){
                    while(p < vec[i].size() && vec[i][p] < vec[j][q]){
                        tmp[len++] = i;
                        ++p;
                    }
                    while(q < vec[j].size() && vec[i][p] > vec[j][q]){
                        tmp[len++] = j;
                        ++q;
                    }
                    if(p == vec[i].size()){
                        while(q < vec[j].size()){
                            tmp[len++] = j;
                            ++q;
                        }
                    }
                    if(q == vec[j].size()){
                        while(p < vec[i].size()){
                            tmp[len++] = i;
                            ++p;
                        }
                    }
                }
                int last = tmp[0], tmp1 = 1;
                for(int k = 1; k < len; ++k){
                    if(tmp[k] == last) continue ;
                    else{
                        last = tmp[k];
                        ans = max(ans, ++tmp1);
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}