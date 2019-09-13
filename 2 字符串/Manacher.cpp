//���������ַ��󣬵�iΪ����������ִ��ĳ����ǰ뾶p[i] - 1, ��ʼλ�����м�λ�ü�ȥ�뾶�ٳ���2
char str[maxn << 1]; //note
int p[maxn << 1]; //note !!!
void Manacher(char s[], int n){
    str[0] = '$', str[1] = '#';
    for(int i = 0; i < n; ++i) str[(i << 1) + 2] = s[i], str[(i << 1) + 3] = '#';
    n = n * 2 + 2; // note
    str[n] = '\0';
    int mx = 0, id;
    for(int i = 1; i < n; ++i){
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while(str[i - p[i]] == str[i + p[i]]) ++p[i];
        if(p[i] + i > mx) mx = p[i] + i, id = i;
    }
}
//������iΪ���(��β)�Ļ����ִ�����
int pre[maxn], suf[maxn];
void calc(int n){
    int up = (n << 1);
    for(int i = up; i >= 2; --i){
        int pos = i / 2;
        ++pre[pos], --pre[pos - (p[i] / 2)];
    }
    for(int i = n; i >= 1; --i){
        pre[i] += pre[i + 1];
    }
    for(int i = 2; i <= up; ++i){
        int pos = (i + 1) / 2; //��ȡ��
        ++suf[pos], --suf[pos + p[i] / 2]; 
    }
    for(int i = 1; i <= n; ++i){
        suf[i] += suf[i - 1];
    }
}