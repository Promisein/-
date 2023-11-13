#include <iostream>
using namespace std;
int main()
{
    // 在输入字符串的每一个位置统计每个字母出现次数的前缀和
    int n; // 长度为n的字符串
    cin >> n;
    // 先建立一个统计字符串每一个位置出现的字母的数组
    char *c = new char[n + 1];
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    int **arr = new int *[27];
    int **sum = new int *[27];
    for (int i = 0; i < 27; i++)
    {
        arr[i] = new int[n + 2];
        sum[i] = new int[n + 2];
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            arr[j][i] = 0;
            sum[j][i] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        int temp = int(c[i]) - int('A');
        arr[temp][i + 1] = 1; // 记录这个字母在字符串出现一次
    }

    // 计算前缀和
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            sum[j][i] = sum[j][i - 1] + arr[j][i];
        }
    }
    // for (int i = 0; i <= n; i++)
    // {
    //     for (int j = 0; j < 26; j++)
    //     {
    //         cout << sum[j][i];
    //     }
    //     cout << endl;
    // }
    int m; // 操作的次数
    cin >> m;
    while (m != 0)
    {
        int l, r; // 左右区间 l 从一开始 ，r到n；
        cin >> l >> r;
        bool judge = true;
        for (int j = 0; j < 26; j++)
        {
            if (sum[j][r] - sum[j][l - 1] == 0)
            {
                judge = false;
            }
        }

        if (judge)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
        m--;
    }
    delete[] c;
    delete[] arr;
    return 0;
}