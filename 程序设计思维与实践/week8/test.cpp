#include <iostream>
using namespace std;

// 定义一个结构体，里面有两个成员，一个为int，一个为double
struct myStruct
{
    int a;
    double b;
    // 思考一个结构体怎么比较大小呢？是通过比较a还是b？
    // 所以要自己定义，重载大于号＞
    bool operator > (myStruct temp)
    {
        return a > temp.a;   //  我这里定义的比较a
    }
};

template <class T>
T getmax(T a, T b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    // 我要比较两个整形数的大小
    int a = 10;
    int b = 4;
    int ans = getmax<int>(a, b);
    cout << "int max: " << ans << endl;

    // 假如我还要比较两个浮点数的大小，怎么办呢？我可不想重写一个函数
    // 利用模板类，将模板换成double就行了

    double x = 0.12;
    double y = 45.12;
    double ans2 = getmax<double>(x, y);
    cout << "double max: " << ans2 << endl;

    // 假如我还要比较结构体的大小呢？
    myStruct xx;
    xx.a = 4;
    xx.b = 1.23;
    myStruct yy;
    yy.a = 8;
    yy.b = 45.23;
    myStruct ans3 = getmax<myStruct>(xx, yy);
    cout << ans3.a << " " << ans3.b << endl;
    return 0;
}