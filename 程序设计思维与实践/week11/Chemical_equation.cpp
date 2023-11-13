#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
using namespace std;
// 分割等于号,如果是大写字母，那么就读取元素，而且读取系数
// 如果遇到左括号，递归调用，直到读取到右括号
// 最后加入统计结果

vector<string> split(const string &str, char split_char)
{
    stringstream ss(str);
    string temp;
    vector<string> result;
    while (getline(ss, temp, split_char))
    {
        if (split_char == '=')
        {
            result.push_back(temp);
        }
        else
        {
            if (split_char == '+')
            {
                result.push_back(temp);
            }
        }
    }
    return result;
}

// 把化学式与其对应的系数加起来
void merge(int &coef, map<string, int> &result, map<string, int> &total)
{
    for (auto &i : result)
    {
        total[i.first] += i.second * coef;
    }
}

// 读取化学式系数的函数，传入的参数为化学式和已经读取到当前化学式的第几位
int readCoef(const string &formula, int &p)
{
    int coef = 0;
    while (p < formula.length() && isdigit(formula[p]))
    {
        coef = coef * 10 + (formula[p] - '0');
        p++;
    }
    if (coef == 0)
    {
        coef = 1;
    }
    return coef;
}

string readElement(const string &formula, int &p)
{
    string name;
    name += formula[p];
    ++p;
    if (/*p < formula.length() &&*/ islower(formula[p]))
    {
        name += formula[p];
        ++p;
    }
    return name;
}
// 对化学式进行解析
map<string, int> praseElement(const string &formula, int &p)
{
    map<string, int> total;
    while (p < formula.length())
    {

        if (formula[p] == '(')
        {
            p++;
            auto result = praseElement(formula, p);
            ++p; // 最后遇到有括号直接略过
            int coef = readCoef(formula, p);
            merge(coef, result, total);
        }
        else
        {
            if (formula[p] == ')')
            {
                return total;
            }
            else
            {
                string element = readElement(formula, p);
                int coef = readCoef(formula, p);
                total[element] += coef;
            }
        }
    }
    return total;
}

// 关于如何判别这个等式左右的元素个数是否相等，使用map来存贮分化出来的结果
map<string, int> parseFormula(const string &exper)
{
    vector<string> formulas = split(exper, '+');
    map<string, int> total; // 总计所有化学式的集合
    for (auto &formula : formulas)
    {
        // 分离化学式的系数
        int p = 0; // 已经读取到当前化学式的第几位
        int coef = readCoef(formula, p);
        auto result = praseElement(formula, p);
        merge(coef, result, total);
    }

    return total;
}
int main()
{
    int n;
    cin >> n;
    while (n != 0)
    {
        string str;
        cin >> str;
        vector<string> equation = split(str, '='); // 等式两端的结果

        map<string, int> left, right;
        left = parseFormula(equation[0]);
        right = parseFormula(equation[1]);
        if (left == right)
        {
            cout << "Y" << endl;
        }
        else
        {
            cout << "N" << endl;
        }
        n--;
    }

    return 0;
}