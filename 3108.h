#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int N;

bool check(vector<pair<int,int>>& a, vector<pair<int,int>>& b) {
	int sum = 0;
	int x0 = a[0].first, y0 = a[0].second;
	int x1 = a[1].first, y1 = a[1].second;
	int x2 = a[2].first, y2 = a[2].second;
	int x3 = a[3].first, y3 = a[3].second;
	for (int i = 0; i < 4; ++i) {
		int x = b[i].first, y = b[i].second;
		if (((x == x1 || x == x2) && (y >= y0 && y <= y1)) ||
			(x >= x0 && x <= x2) && (y == y0 || y == y1))
			return true;
		if (x > x0 && x < x2 && y > y0 && y < y1) continue;
		
		else sum++;
		
	}
	if (sum == 4 || sum == 0) return false;
	else return true;
}

int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	vector<vector<pair<int,int>>> v(N+1);
	vector<pair<int, int>> v_tmp(4);
	vector<int> visit(N+1,-1);
	v_tmp[0] = make_pair(0, 0);
	v_tmp[1] = make_pair(0, 0);
	v_tmp[2] = make_pair(0, 0);
	v_tmp[3] = make_pair(0, 0);
	v[0] = v_tmp;
	for (int i = 1; i < N+1; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		v_tmp[0] = make_pair(x1, y1);
		v_tmp[1] = make_pair(x1, y2);
		v_tmp[2] = make_pair(x2, y2);
		v_tmp[3] = make_pair(x2, y1);
		sort(v_tmp.begin(), v_tmp.end());
		v[i] = v_tmp;
	}
	int cnt = 0;
	for (int i = 0; i < N +1; ++i) {
		if (visit[i] != -1) continue;
		visit[i] = cnt;
		queue<int> q;
		q.push(i);
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			for (int j = i; j < N + 1; ++j) {
				if (visit[j] != -1 || !check(v[now],v[j])) continue;
				visit[j] = cnt;
				q.push(j);
			}
		}
		++cnt;
	}
	cout << cnt - 1 << '\n';
	
	
	return 0;
}