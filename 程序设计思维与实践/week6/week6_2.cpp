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
    char last = 'x';
    for (int i = 0; i < str.size(); i++)
    {
        if(judge(str[i]))
        {
            if(!judge(last))
            {
                cout << str[i];
            }
        }
        else
        {
            cout << str[i];
        }
        last = str[i];
    }
    cout << endl;

}
