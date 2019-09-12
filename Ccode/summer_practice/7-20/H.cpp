#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
char s[maxn][maxn];
int h[maxn];
int main(){
    int n,m;
    while(~scanf("%d%d",&n, &m)){
        for(int i = 0; i < n; ++i){
            scanf("%s",s[i]);
        }
        for(int i = 0; i <= m; ++i) h[i] = 0;
        int ans = 0;
        stack<int>sta;
        priority_queue<int, vector<int>, greater<int> >q;
        for(int i = 0; i < n; ++i){
            while(!sta.empty()) sta.pop();
            bool ok = false;
            for(int j = 0;j <= m; ++j){
                if(j < m && !ok){
                    if(s[i][j] == '1'){
                        if(i > 0 && s[i-1][j]=='1') ++h[j];
                        else h[j] = 1;
                    }
                    else h[j] = 0;
                }
                if(sta.empty() || h[j] > h[sta.top()]){
                    sta.push(j);
                    ok = false;
                }
                else{
                    int tmp = sta.top();
                    sta.pop();
                    int y = h[tmp] * (sta.empty()? j :j - sta.top() - 1);
                    ans = max(ans,y);
                    if(y) q.push(y);
                    --j, ok = true; 
                    while(q.size() >= 3){
                        q.pop();
                    } 
                }
            }
        }
        if(q.size() <= 1){
            printf("0\n"); continue ;
        }else{
            ans = q.top();
            printf("%d\n",ans);
        }
    }
    return 0;
}

