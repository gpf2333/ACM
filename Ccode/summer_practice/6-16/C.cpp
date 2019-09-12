#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 100;
int x[maxn],l[maxn],d[maxn];
struct Node{
    int id, d;
    Node(){}
    Node(int _d, int _id){
        d = _d, id = _id;
    }

    bool operator < (const Node &b) const{
        if(d == b.d) return id > b.id;
        return d > b.d;
    }
};

int main(){
    priority_queue<Node>q;
    int n, m;
    scanf("%d%d",&n, &m);
    for(int i = 0; i < n; ++i){
        scanf("%d",&x[i]);
    }
    for(int i = 0; i < m; ++i){
        scanf("%d",&l[i]);
    }
    for(int i = n - 1; i >= 0; --i){
        d[i] = x[i] - x[i - 1];
    }
    d[0] = 0;

    for(int i = 1; i < n; ++i){
        q.emplace(d[i], i + 1);
    }
    sort(l, l + m);
    int cnt = 0;
    while(!q.empty() && cnt < m){
        Node cur = q.top(); q.pop();
        if(cur.id < n){
            q.emplace(cur.d + d[cur.id], cur.id + 1);
        }

        if(l[cnt] >= cur.d){
            ++cnt;
        } else {
            break ;
        }
    }
    if(cnt == m){
        puts("yes");
    }else{
        puts("no");
    }
    return 0;
}