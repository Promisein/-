#include <bits/stdc++.h>
using namespace std;

deque<string> sp[4];               // 0->牌堆，1、2、3分别是三个人的手牌
bool dir = 1, flag = 0, ischu = 0; // 方向，是否更新过cur，是否出过牌
int cur = 1, n;                    // 现在谁出牌
char color_cur, num_cur, like[4];  // 现在要出的颜色和数字和他们喜欢的颜色
string tmp, pai, name[4] = {"No one", "zxf", "ptx", "ysl"};

inline void updateCur(char c, char x) {	num_cur = c, color_cur = x; }

inline void updateCur(string x) { num_cur = x[0], color_cur = x[1]; }

inline bool match(string x) { return x[0] == num_cur or x[1] == color_cur or x[0] == 'W'; }

inline void changeDir() { dir ^= 1; }

inline void skip() { cur = (dir ? (cur + 2) : (cur + 1)) % 3, cur = (cur == 0) ? 3 : cur, flag = 1; }

inline void isWin() {
	if (sp[cur].empty()) { // 是否有人打完了牌
		cout << name[cur] << " wins URA!\n"
		     << pai;
		exit(0);
	}
}

inline void isEnd() { 
	if (sp[0].empty()) { // 牌被摸完了但是还有人要摸牌，游戏结束
		cout << "No one wins URA!\n"
		     << pai;
		exit(0);
	}
}
inline void nextGet(int n) { // 下一个人摸牌
	int k = dir ? (cur == 3 ? 1 : cur + 1) : (cur == 1 ? 3 : cur - 1);
	while (n--) {
		isEnd();
		sp[k].emplace_back(sp[0].front());
		sp[0].pop_front();
	}
}
inline void isFunction() {
	if (pai[1] == '4')
		nextGet(4), skip();
	else if (pai[0] == 'S')
		skip();
	else if (pai[0] == 'R')
		changeDir();
	else if (pai[0] == 'D')
		nextGet(2), skip();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	for (int i = 1; i <= 3; ++i)
		for (int j = 0; j < 7; ++j) {
			cin >> tmp;
			sp[i].emplace_back(tmp);
		}
	
	cin >> num_cur >> color_cur >> like[1] >> like[2] >> like[3] >> n;
	
	for (int i = 0; i < n; ++i) {
		cin >> tmp;
		sp[0].emplace_back(tmp);
	}
	
	while (1) {
		flag = 0, ischu = 0;
		for (auto it = sp[cur].begin(); it != sp[cur].end(); ++it) {
			if (match((*it))) { 				// 找到能打的牌
				ischu = 1;                      // 已经出牌
				pai = (*it), sp[cur].erase(it); // 更新并删除要打出的牌
				isWin();
				pai[0] == 'W' ? updateCur('#', like[cur]) : updateCur(pai);
				isFunction();
				break;
			}
		}
		if (!ischu) { // 没出牌
			isEnd();
			if (match(sp[0].front())) {
				pai = sp[0].front();
				sp[0].pop_front();
				pai[0] == 'W' ? updateCur('#', like[cur]) : updateCur(pai);
				isFunction();
			} else {
				sp[cur].push_back(sp[0].front());
				sp[0].pop_front();
			}
		}
		if (!flag) { // 没有更新过cur
			dir ? ++cur : --cur;
			if (cur == 0)
				cur = 3;
			else if (cur == 4)
				cur = 1;
		}
	}
	return 0;
}
