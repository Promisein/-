#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

string LCS(string firstStr, string secondStr) {
    int x = firstStr.size() + 1;
    int y = secondStr.size() + 1;
    // 申请动态生成的二维数组
    int** cArray = new int* [x];
    int** sArray = new int* [x];
    for (int i = 0; i < x; i++) {
        cArray[i] = new int[y];
        sArray[i] = new int[y];
    }
    // 初始化动态生成的cArray
    for (int j = 0; j < y; j++) {
        cArray[0][j] = 0;
        sArray[0][j] = 0;
    }
    for (int i = 0; i < x; i++) {
        cArray[i][0] = 0;
        sArray[i][0] = 0;
    }
    string result = "";
    // 开始处理两个字符串
    for (int i = 1; i <= firstStr.length(); i++) {
        for (int j = 1; j <= secondStr.length(); j++) {
            if (secondStr[j - 1] == firstStr[i - 1]) {
                cArray[i][j] = cArray[i - 1][j - 1] + 1;
                sArray[i][j] = 1;
            }
            else {
                if (cArray[i][j - 1] <= cArray[i - 1][j]) {
                    cArray[i][j] = cArray[i - 1][j];
                    sArray[i][j] = 2;
                }
                else {
                    cArray[i][j] = cArray[i][j - 1];
                    sArray[i][j] = 3;
                }
            }
        }
    }
    int i = firstStr.size();
    int j = secondStr.size();
    while (i >= 1 && j >= 1) {
        if (sArray[i][j] == 1) {
            result += firstStr[i - 1];
            i--;
            j--;
        }
        else if (sArray[i][j] == 2) {
            i--;
        }
        else if (sArray[i][j] == 3) {
            j--;
        }
    }
    // 反转字符串
    int m = result.size() / 2;
    for (int j = 0; j < m; j++) {
        char temp = result[j];
        result[j] = result[result.size() - 1 - j];
        result[result.size() - 1 - j] = temp;
    }
    return result;
}

int main() {
    string firstStr;
    string secondStr;
    cout << "Enter first string: ";
    cin >> firstStr;
    cout << "Enter second string: ";
    cin >> secondStr;
    string result = LCS(firstStr, secondStr);
    if (result.size() == 0) {
        cout << "No common string between two strings.\n";
    }
    else {
        cout << "The longest common string is " << result << endl;
    }
}
