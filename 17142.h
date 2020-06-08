#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int N, M;
int A[50][50];
vector<pair<int, int>> v;
vector<int> selec;
int ans = 987654321, dy[4] = { 0,1,0,-1 }, dx[4] = {1,0,-1,0};
int tmp[50][50];
int count() {
	int sum = 0;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			if (tmp[j][i] == 0) ++sum;
		}
	}
	return sum;
}

void bfs() {
	memcpy(tmp, A, sizeof(A));
	
	queue<pair<int,int>> q;
	for (int i = 0; i<int(selec.size()); ++i) {
		q.push(make_pair(v[selec[i]].first, v[selec[i]].second));
		tmp[v[selec[i]].first][v[selec[i]].second] = 3;
	}

	int time = 0;
	int init_cnt = count();
	while(!q.empty()) {
		++time;
		int length = q.size();
		for (int i = 0; i < length; ++i) {
			int y = q.front().first, x = q.front().second; q.pop();
			for (int d = 0; d < 4; ++d) {
				int ny = y + dy[d], nx = x + dx[d];
				if (ny<0 || nx<0 || ny>=N || nx>=N || tmp[ny][nx] == 1 ||tmp[ny][nx]==3) continue;
				if (tmp[ny][nx] == 0) init_cnt--;
				q.push(make_pair(ny, nx));
				tmp[ny][nx] = 3;
			}
		}
		if (!init_cnt) {
			ans = min(time, ans);
			break;
		}
	}
	
}

void dfs(int cnt,int start) {
	if (cnt == M) {
		bfs();
		return;
	}
	
	for (int i = start; i<int(v.size()); ++i) {
		selec.push_back(i);
		dfs(cnt + 1, i + 1);
		selec.pop_back();
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			cin >> A[j][i];
			if (A[j][i] == 2) v.push_back(make_pair(j,i));
		}
	}
	memcpy(tmp, A, sizeof(A));
	if (!count()) {
		cout << 0 << '\n';
		return 0;
	}
	dfs(0,0);
	if (ans==987654321) cout << -1 << '\n';
	else cout << ans << '\n';
	return 0;
}