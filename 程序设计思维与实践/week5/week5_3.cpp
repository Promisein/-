#include <iostream>
#include <deque>
#include <fstream>
// 找最大值就维护递减序列，找最小值就维护递增序列
using namespace std;
int main()
{
    // 2023年3月25日21:06:41
    deque<pair<int, long>> max; // 递减序列
    deque<pair<int, long>> min; // 递增序列
    // 人生建议：存储数组里面的下标比较好（这个建议不一定准确哦）
    int n, k;
    cin >> n >> k;
    pair<int, long> *arr = new pair<int, long>[n + 1];
    for (int i = 1; i <= n; i++)
    {
        arr[i].first = i;
        cin >> arr[i].second;
    }

    // 递增找最小值
    // 先把前k个元素压入队列
    for (int i = 1; i <= k; i++)
    {
        while (true)
        {
            if (min.empty() || min.back().second < arr[i].second)
            {
                min.push_back(arr[i]);
                break; // 压入一个元素就开始判断是否越界
            }
            else
            {
                min.pop_back();
            }
        }
    }
    int index = 0;
    long *__MIN__NUMBER = new long[n];
    __MIN__NUMBER[index] = min.front().second;
    index++;
    for (int i = k + 1; i <= n; i++)
    {
        while (true)
        {
            if (min.empty() || min.back().second < arr[i].second)
            {
                min.push_back(arr[i]);
                break; // 压入一个元素就开始判断是否越界
            }
            else
            {
                min.pop_back();
            }
        }
        while (true)
        {
            int __MIN__INDEX = min.front().first;
            if (__MIN__INDEX < i - k + 1) // 这个最小值已经超出了范围
            {
                min.pop_front();
            }
            else
            {
                break;
            }
        }
        __MIN__NUMBER[index] = min.front().second;
        index++;
    }

    // 递减找最大值
    for (int i = 1; i <= k; i++)
    {
        while (true)
        {
            if (max.empty() || max.back().second > arr[i].second)
            {
                max.push_back(arr[i]);
                break; // 压入一个元素就开始判断是否越界
            }
            else
            {
                max.pop_back();
            }
        }
    }
    index = 0;
    long *__MAX__NUMBER = new long[n];
    __MAX__NUMBER[index] = max.front().second;
    index++;
    for (int i = k + 1; i <= n; i++)
    {
        while (true)
        {
            if (max.empty() || max.back().second > arr[i].second)
            {
                max.push_back(arr[i]);
                break; // 压入一个元素就开始判断是否越界
            }
            else
            {
                max.pop_back();
            }
        }
        while (true)
        {
            int __MAX__INDEX = max.front().first;
            if (__MAX__INDEX < i - k + 1)
            {
                max.pop_front();
            }
            else
            {
                break;
            }
        }
        __MAX__NUMBER[index] = max.front().second;
        index++;
    }

    for (int i = 0; i < index; i++)
    {
        cout << __MIN__NUMBER[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < index; i++)
    {
        cout << __MAX__NUMBER[i] << " ";
    }
    cout << endl;
    delete[] arr;
    delete[] __MIN__NUMBER;
    delete[] __MAX__NUMBER;
    return 0;
}