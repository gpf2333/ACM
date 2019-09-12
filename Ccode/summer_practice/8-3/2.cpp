#include <bits/stdc++.h>
using namespace std;
string addr;
vector<char> s[10];
vector<char> ans[10];
vector<char> anss[10];
int main(){
    int t;
    cin >> t;
    int cas = 0;
    while(t--){
        cin >> addr;
        for(int i = 0; i < 8; i++)
            s[i].clear(), ans[i].clear(), anss[i].clear();
        for(int i = 0; i < addr.size() / 16; i ++){
            for(int j = 0; j <4; j ++){
                int tmp = 0;
                for(int k = 0; k < 4; k++){
                    tmp = tmp * 2 + addr[i * 16 + j * 4 + k] - '0';
                }
                char c;
                if(tmp == 10) c = 'a';
                else if(tmp == 11) c = 'b';
                else if(tmp == 12) c = 'c';
                else if(tmp == 13) c = 'd';
                else if(tmp == 14) c = 'e';
                else if(tmp == 15) c = 'f';
                else c = tmp + '0';
                s[i] .push_back(c);
            }
        }
        for(int i = 0; i < 8; i++){
            bool flag = false;
            int cnt = 0;
            for(int j = 0; j < s[i].size(); j++){
                if(!flag && s[i][j] == '0'){
                    cnt++;
                }
                else if(!flag && s[i][j] != '0'){
                    flag = true;
                }
            }
            if(cnt){
                if(!flag){
                    ans[i].push_back('0');
                }
                else{
                    for(int j = cnt; j < 4; j++ ){
                        ans[i].push_back(s[i][j]);
                    }
                }
            }
            else{
                for(int j = 0; j < 4; j++){
                    ans[i].push_back(s[i][j]);
                }
            }
        }
        int maxlen = 0;
        int posl = -1;
        int posr = -1;
        int cnt = 0;
        bool ff = false;
        bool fff = false;
        for(int i = 7; i >= 0; i--){
            if(ans[i].size() == 1 && ans[i][0] == '0'){
                cnt++;
                if(cnt >= 2){
                    if(maxlen == cnt && ff && !fff){
                        posl = i;
                        posr = i + cnt - 1;
                        fff = true;
                    }
                    if(maxlen < cnt){
                        maxlen = cnt;
                        posl = i;
                        posr = i + cnt - 1;
                        if(posr == 7){
                            ff = true;
                        }
                    }
                }
            }
            else{
                cnt = 0;
            }
        }
        for(int i = 0; i < 8; i++){
            for(auto j:ans[i]){
                cout << j ;
            }
            cout << endl;
        }
        bool is = false;
        cout << posl << " " << posr << endl;
        cout << "Case #" << ++cas << ": ";
        for(int i = 0; i < 8; i++){
            if(i >= posl && i <=posr){
                if(i == posl || i == posr){
                    cout << ":";
                }
                else
                    continue;
            }
            else{
                if(i != 0 && i - 1 != posr)
                    cout << ":";
                for(char j: ans[i]){
                    cout << j;
                }
            }
        }
        cout << endl;
    }
}