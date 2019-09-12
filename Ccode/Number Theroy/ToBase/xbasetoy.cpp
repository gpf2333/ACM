#include <iostream>
using namespace std;

// x进制转换为y进制
int conversion(int in[], int out[], int n, int x, int y) {
    // 转换为y进制之后的长度
    int size = 0;
    // 每次迭代是一次除法
    int i = 0;
    while (i < n) {
        int remainder = 0;
        int dividend;
        // 每次迭代是一位数字的除法
        for (int j = i; j < n; j++) {
            dividend = remainder * x + in[j];
            in[j] = dividend / y;
            remainder = dividend % y;
        }
        out[size++] = remainder;
        //去除商前面所有的0
        while (in[i] == 0 && i < n) i++;
    }
    return size;
}


int main() {
    string s;
    int in[100];
    int out[100];
    while (cin >> s) {
        // 输入
        int n = s.length();
        for (int i = 0; i < n; i++) {
            in[i] = s[i] - '0';
        }

        // 10进制转换为2进制
        int size = conversion(in, out, n, 10, 2);

        // 输出，需要逆序输出
        for (int i = size - 1; i >= 0; i--) {
            cout << out[i];
        }
        cout << endl;
    }
}

