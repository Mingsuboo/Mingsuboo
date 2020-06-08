#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int L, C;
vector<char> A;
vector<char> fi;
int cnt_a = 0, cnt_b = 0;
void dfs(int cnt, int start) {
	if (cnt == L) {
		if (cnt_a >= 1 && cnt_b >= 2) {
			for (int i = 0; i < L; ++i) cout << fi[i];
			cout << '\n';
		}
		return;
	}
	for (int i = start; i <= C - (L - cnt); ++i) {
		int tmp_a = cnt_a, tmp_b = cnt_b;
		if (A[i] == 'a' || A[i] == 'e' || A[i] == 'i' || A[i] == 'o' || A[i] == 'u') cnt_a++;
		else cnt_b++;
		fi.push_back(A[i]);
		dfs(cnt + 1, i + 1);
		fi.pop_back();
		cnt_a = tmp_a, cnt_b = tmp_b;
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> L >> C;
	for (int i = 0; i < C; ++i) {
		char tmp;
		cin >> tmp;
		A.push_back(tmp);
	}
	sort(A.begin(), A.end());
	reverse(A.begin(), A.end());
	dfs(0,0);
	return 0;
}