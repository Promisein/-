#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 100;
int arr[maxn];
int f[maxn];    // arr_i 为结尾的最长上升序列的长度。
int tree[maxn]; // 树状数组,树状数组维护的前i个数的最大值
int lowbit(int x)
{
    return (x & (-x));
}

void update(int pos, int val)
{
    for (int i = pos; i <= maxn; i += lowbit(i))
    {
        tree[i] = max(tree[i], val);
    }
}

int ask(int pos)
{
    int temp = 0;
    for (int i = pos; i >= 1; i -= lowbit(i))
    {
        temp = max(temp, tree[i]);
    }
    return temp;
}

int FUNCTION(int n)
{
    int ans = 0;
    f[1] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i] = ask(arr[i] - 1) + 1;
        update(arr[i], f[i]);
        ans = max(ans, f[i]);
    }
    return ans;
}

int main()
{
    memset(arr, 0, sizeof(arr));
    memset(f, 0, sizeof(f));
    memset(arr, 0, sizeof(arr));

    int n;
    cin >> n;
    for (size_t i = 1; i <= n; i++)
    {
        /* code */
        cin >> arr[i];
    }
    cout << FUNCTION(n) << endl;
    return 0;
}