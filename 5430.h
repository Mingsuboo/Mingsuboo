#include <iostream>
#include <vector>
#include <deque>

using namespace std;
int T;
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	for (int tc = 0; tc < T; ++tc) {
		string com, array; int len; deque<int>v;
		cin >> com >> len >> array;
		int k = 1;
		char now = array[1];
		int sum = 0;
		while (true) {
			if (now == ',' || now==']') {
				if (sum!=0) v.push_back(sum);
				sum = 0;
				if (now == ']') break;
			}
			else {
				sum = sum * 10 + (now - '0');
			}
			++k;
			now = array[k];
		}
		bool flag = false;
		bool error = false;
		for (int i = 0; i<com.size(); ++i) {
			char c = com[i];
			if (c == 'R') flag = !flag;
			else {
				if (v.size() == 0) {
					error = true;
					break;
				}
				else if (!flag) {
					v.pop_front();
				}
				else if (flag) {
					v.pop_back();
				}
			}
		}
		if (error) cout << "error" << '\n';
		else {
			cout << '[';
			if (flag) {
				for (int i = int(v.size())-1; i>=0; --i) {
					cout << v[i];
					if (i != 0) cout << ',';
				}
			}
			else {
				for (int i = 0; i < int(v.size()); ++i) {
					cout << v[i];
					if (i != v.size() - 1) cout << ',';
				}
			}
			cout << ']' << '\n';
		}
	}
	return 0;
}