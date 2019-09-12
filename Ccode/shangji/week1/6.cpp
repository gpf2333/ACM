#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int fa[maxn], h[maxn],Size[maxn];

void init(){
    for(int i = 0; i < maxn; ++i) {
        fa[i] = i, h[i] = 0, Size[i] = 1;
    }
}

int Find(int x){
    while(x != fa[x]){
        x = fa[x];
    }
    return x;
}

void union_1(int i, int j){
    i = Find(i), j = Find(j);
    if(i != j){
        fa[j] = i;
    }
}

void up_h(int x){
    ++h[x];
    while(x != fa[x]){
        x = fa[x], ++h[x];
    }
}

void union_2(int i, int j){
    if((i = (Find(i))) == (j = Find(j))) return ;
    if(h[i] == h[j]){
        fa[j] = i;
        up_h(i);
    } else if(h[i] > h[j]){
        fa[j] = i;
    } else {
        fa[i] = j;
    }
}

void up_child(int x, int d){
    Size[x] += d;
    while(x != fa[x]){
        x = fa[x];
        Size[x] += d;
    }
}

void union_3(int i, int j){
    i = Find(i), j = Find(j);
    if(i == j) return ;
    cout << i << " " << j << endl;
    if(Size[i] >= Size[j]){
        fa[j] = i;
        Size[i] += Size[j]; 
    } else{
        fa[i] = j;
        Size[j] += Size[i];
    }
}

void out_put(int x){
    cout << x << " ";
    while(x != fa[x]){
        x = fa[x];
        cout << x << " ";
    }
    cout << endl;
}

int main(){
    init();
    int x, y;
    for(int i = 0; i < 16; ++i){
        cin >> x >> y;
        union_1(x, y);
        //union_2(x, y);
        //union_3(x, y);
    }
    cout << "节点链：" << endl;
    for(int i = 0; i <= 16; ++i){
        out_put(i);
    }
    system("pause");
    return 0;
}


// #include<bits/stdc++.h>
// using namespace std;
// int main()
// {
//     int x  = 123;
//     string s = std::to_string(x);
//     cout << s << endl;
//     system("pause");
//     return 0;
// }

/*
1 2
3 4
3 5
1 7
3 6
8 9
1 8
3 10
3 11
3 12
3 13
14 15
16 0
14 16
1 3
1 14
*/