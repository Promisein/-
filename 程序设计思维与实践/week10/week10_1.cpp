#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int max_length = 1;
void function(int position, string str) // 在每一个位置判断回文的大小
{
    // 判断是奇数那种的回文数

    size_t left, right;
    left = position - 1;
    right = position + 1;
    int temp_max_length = 1;
    while (left >= 0 && right < str.length())
    {
        if (str[left] == str[right])
        {
            temp_max_length += 2;
            max_length = max(temp_max_length, max_length);
            left--;
            right++;
        }
        else
        {
            break;
        }
    }

    size_t left2, right2;
    left2 = position - 1;
    right2 = position;
    int temp_max_length2 = 0;
    while (left2 >= 0 && right2 < str.length())
    {

        if (str[left2] == str[right2])
        {
            temp_max_length2 += 2;
            max_length = max(temp_max_length2, max_length);
            left2--;
            right2++;
        }
        else
        {
            break;
        }
    }
}
int main()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    for (size_t i = 0; i < n; i++)
    {
        if (str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            str[i] = 'a';
        }
    }
    // cout << str << endl;
    for (int i = 1; i < n; i++)
    {
        function(i, str);
    }
    cout << max_length << endl;
    return 0;
}
