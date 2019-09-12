#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int n, m;
vector<int> mp[maxn];
vector<int> G[maxn];
int num[maxn];
vector<int> ans;
int d[27];
int in[maxn];
int tot;
int main()
{
    cin >> n >> m;
    m = m * (m - 1) / 2;
    tot = 0;
    while(m--){
        int t;
        string a, b;
        cin >> a >> t;
        if(!t) cin >> b;
        else getchar();
        memset(d, 0, sizeof(d));
        int last = -1;
        for(int i = 0; i < t; i ++){
            int id = b[i] - 'a';
            d[id] ++;
            if(mp[id].size() < d[id]){
                mp[id].push_back(tot++);
                num[tot] = id;
            }
            if(last != - 1){
                G[last].push_back(mp[id][d[id] - 1]);
                in[mp[id][d[id] - 1]];
            }                
            last = mp[id][d[id] - 1];
        }
    }
    if(tot != n){
        puts("-1");
        return 0;
    }
    queue<int> q;
    for(int i = 1; i <= tot; i++){
        if(!in[i]) q.push(i); 
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        ans.push_back(u);
        for(int v: G[u]){
            in[v]--;
            if(!in[v]){
                q.push(v);
            }
        }
    }
    if(ans.size() != n){
        puts("-1");
        return 0;
    }
    for(auto i : ans){
        cout << num[i];
    }
    cout << endl;
    
    return 0;
}