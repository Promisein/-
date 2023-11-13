#include <iostream>
using namespace std;
// 利用尺取法解决问题
int main()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    int character[26] = {0};
    int __MIN__LENGTH = n;
    // 开始尺取法
    int left = 0, right = -1;
    int __EXSIT__LENGTH = 0;
    while (left < n - 25) // 尺取法已经到头了
    {
        // right的移动条件
        if (__EXSIT__LENGTH < 26 && right < n - 1)
        {
            right++;
            if (character[int(str[right] - 'A')] == 0)
            {
                __EXSIT__LENGTH++;
            }
            character[int(str[right] - 'A')]++;
            
        }

        // 左指针移动的条件
        if (__EXSIT__LENGTH == 26 || right == n - 1)
        {
            if (__EXSIT__LENGTH == 26)
            {
                __MIN__LENGTH = min(__MIN__LENGTH, right - left + 1);
            }
            character[int(str[left] - 'A')]--;  // 当前的字符数量减一
            if (character[int(str[left] - 'A')] == 0) 
            {
                __EXSIT__LENGTH--;       // 如果已经减少的没了，那么就已经存在的长度减一。
            }
            
            left++;
        }
    }

    cout << __MIN__LENGTH << endl;
    return 0;
}