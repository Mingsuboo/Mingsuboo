#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;
int r, c, k;
int max_r, max_c;
int A[101][101];
int cnt[101];
bool check() {
	return A[r][c] == k;
}
bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.second < b.second) return true;
	else if (a.second == b.second) {
		if (a.first < b.first) return true;
	}
	return false;
}
void init() {
	for (int j = 0; j < 101; ++j)
		for (int i = 0; i < 101; ++i)
			A[j][i] = 0;
}
void row_sort(vector<vector<int>>v) {
	init();
	int row = v.size();
	int col = v[0].size();
	for (int j = 0; j < row; ++j) {
		map<int, int> m;
		for (int i = 0; i < col; ++i) {
			int now = v[j][i];
			if (now == 0) continue;
			if (m.find(now) == m.end()) m[now] = 1;
			else m[now] += 1;
		}
		vector<pair<int,int>> tmp;
		for (int c = 1; c < 101; ++c) {
			if (m.find(c) == m.end()) continue;
			tmp.push_back(make_pair(c,m[c]));
		}
		sort(tmp.begin(), tmp.end(), compare);
		int length = tmp.size();
		length = min(50, length);
		max_c = max(max_c, length * 2);
		for (int c = 0; c < length; ++c) {
			A[j][c * 2] = tmp[c].first;
			A[j][c * 2 + 1] = tmp[c].second;
		}
	}
}
void col_sort(vector<vector<int>>v) {
	init();
	int row = v.size();
	int col = v[0].size();
	for (int j = 0; j < row; ++j) {
		map<int, int> m;
		for (int i = 0; i < col; ++i) {
			int now = v[j][i];
			if (now == 0) continue;
			if (m.find(now) == m.end()) m[now] = 1;
			else m[now] += 1;
		}
		vector<pair<int, int>> tmp;
		for (int c = 1; c < 101; ++c) {
			if (m.find(c) == m.end()) continue;
			tmp.push_back(make_pair(c, m[c]));
		}
		sort(tmp.begin(), tmp.end(), compare);
		int length = tmp.size();
		length = min(50, length);
		max_r = max(max_r, length * 2);
		for (int c = 0; c < length; ++c) {
			A[c*2][j] = tmp[c].first;
			A[c*2+1][j] = tmp[c].second;
		}
	}
}

int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> r >> c >> k;
	r--; c--;
	int ans = -1;
	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 3; ++i) {
			cin >> A[j][i];
		}
	}
	max_r = 3; max_c = 3;
	for (int time = 0; time < 101; ++time) {
		if (check()) {
			ans = time;
			break;
		}
		
		if (max_r >= max_c) {
			vector<vector<int>>	v(max_r, vector<int>(max_c, 0));
			for (int j = 0; j < max_r; ++j) {
				for (int i = 0; i < max_c; ++i) {
					v[j][i] = A[j][i];
				}
			}
			row_sort(v);
		}
		else {
			vector<vector<int>>	v(max_c, vector<int>(max_r, 0));
			for (int i = 0; i < max_c; ++i) {
				for (int j = 0; j < max_r; ++j) {
					v[i][j] = A[j][i];
				}
			}
			col_sort(v);
		}
	}
	cout << ans << '\n';
	return 0;
}