#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n, m; // 小木屋的数量，山羊的数量
    cin >> n >> m;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    int left = 1;                    // 最短距离为1
    int right = arr[n - 1] - arr[0]; // 最远距离为两端的距离
    int ans = 0;
    while (left <= right)
    {
        long long mid = (left + right) / 2;
        int min_number = 1; // 记录当前最少能安排多少只山羊
        int now_left = arr[0];
        for (int i = 1; i < n; i++)
        {
            if (arr[i] - now_left >= mid) // 如果点前的小木屋与上一只山羊的距离大于等于mid
            {
                min_number++;      // 往隔壁安排一个山羊
                now_left = arr[i]; // 更新左端点
            }
        }
        if (min_number >= m) //
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << ans << endl;
    delete[] arr;
    return 0;
}