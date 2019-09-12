#include<bits/stdc++.h>
using namespace std;
struct Node{
    double x,y;
    Node(){};
    Node(double xx,double yy):x(xx),y(yy){};
};
inline  double getdis(const Node &a,const Node &b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main(){
    mt19937 rnd(time(0));
    int n;
    scanf("%d",&n);
    if(n>=1000) puts("0");
    else{
        time_t s = clock();//起始时间
        int cnt=0;
        double sum = 0;
        vector<Node>vec;
        //控制时间
        while(clock()-s<1.8*CLOCKS_PER_SEC){
            vec.clear();
            ++cnt;
            for(int i=0;i<n;++i){
                vec.push_back(Node(rnd()%1000000*1.0/1000000,rnd()%1000000*1.0/1000000));
            }
            double tmp = 2.0;
            for(int i=0;i<n;++i){
                for(int j=0;j<i;++j){
                    tmp = std::min(tmp,getdis(vec[i],vec[j]));
                }
            }
            sum += tmp;
        }
        cout<<sum/cnt<<endl;
    }
    return 0;
}

