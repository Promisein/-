#include <iostream>
using namespace std;
bool judge(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {
        return true;
    }
    return false;
    // string str = "aeiou";
    // for (int i = 0; i < 5; i++)
    // {
    //     if (str[i] == c)
    //     {
    //         return true;
    //     }
    // }
    // return false;
}
int main()
{
    int n;
    std::cin >> n;
    std::string str;
    std::cin >> str;
    int max_length = 0;
    int temp_length = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (judge(str[i]))
        {
            temp_length++;
        }
        else
        {
            if (!judge(str[i]))
            {
                if (max_length < temp_length)
                {
                    max_length = temp_length;
                }
                temp_length = 0;
            }
        }
    }
    cout << max_length << endl;

    return 0;
}