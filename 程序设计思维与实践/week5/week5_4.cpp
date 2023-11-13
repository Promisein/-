#include <iostream>
#include <vector>
#include <stack>
// 单调栈的实现
using namespace std;
void output(vector<long long> arr)
{
    for (auto i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
}
// 使用单调递减栈，永远能够找到一个小短的单增序列
int main()
{
    int n;
    cin >> n;
    vector<long long > arr;
    for (int i = 0; i < n; i++)
    {
        long long temp;
        cin >> temp;
        arr.push_back(temp);
    }
    arr.push_back(-10); // 为了在最后能够让所有的数据出栈，所以最后一个设置成为负数

    stack<int> st; // 存储下标
    long long __MAX_AERA = 0;
    int now_top; // 记录当前的高度
    for (int i = 0; i <= n; i++)
    {
        if (st.empty() || arr[st.top()] <= arr[i])
        {
            st.push(i);
        }
        else
        {
            while (!st.empty() && arr[st.top()] > arr[i])
            {
                now_top = st.top();
                st.pop();

                // i-top指的是当前矩形的宽度，heights[top]就是当前的高度
                long long temp = (i - now_top) * arr[now_top];
                if (temp > __MAX_AERA)
                {
                    __MAX_AERA = temp;
                }
            }
            st.push(now_top);
            arr[now_top] = arr[i];
            output(arr);
        }
    }
    cout << __MAX_AERA << endl;
    return 0;
}