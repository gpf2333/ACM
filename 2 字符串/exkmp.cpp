//nxt[i]: x[i...m-1]与x[0...m-1]的最长公共前缀
//extend[i]: y[i...n-1]与x[0...m-1]的最长公共前缀
int nxt[maxn], extend[maxn];
void pre_exkmp(char x[], int m){
    nxt[0] = m;
    int j = 0;
    while(j + 1 < m && x[j] == x[j + 1]) ++j;
    nxt[1] = j;
    int k = 1;
    for(int i = 2; i < m; ++i){
        int p = nxt[k] + k  - 1;
        int L = nxt[i - k];
        if(i + L < p + 1) nxt[i] = L;
        else{
            j = max(0, p - i + 1);
            while(i + j < m && x[i + j] == x[j]) ++j;
            nxt[i] = j, k = i;
        }
    }
}
void exkmp(char x[], int m, char y[], int n){
    pre_exkmp(x, m);
    int j = 0;
    while(j < n && j < m && x[j] == y[j]) ++j;
    extend[0] = j;
    int k = 0;
    for(int i = 1; i < n; ++i){
        int p = extend[k] + k - 1;
        int L = nxt[i - k];
        if(i + L < p + 1) extend[i] = L;
        else{
            j = max(0, p - i + 1);
            while(i + j < n && j < m && y[i + j] == x[j]) ++j;
            extend[i] = j, k = i;
        }
    }
}