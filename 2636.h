#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, M, chz[100][100];
int dy[4] = { 0,1,0,-1 }, dx[4] = {1,0,-1,0};
int count_chz() {
	int cnt = 0;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < M; ++i) {
			if (chz[j][i] == 1) cnt++;
		}
	}
	return cnt;
}
void melt() {
	vector<vector<int>> visit(N, vector<int>(M,0));
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));
	visit[0][0] = 1;
	while (!q.empty()) {
		int y = q.front().first, x = q.front().second;
		q.pop();
		for (int d = 0; d < 4; ++d) {
			int ny = y + dy[d], nx = x + dx[d];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M || visit[ny][nx]==1) continue;
			visit[ny][nx] = 1;
			if (chz[ny][nx] == 0) q.push(make_pair(ny,nx));
		}
	}
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < M; ++i) {
			if (visit[j][i] == 1) chz[j][i] = 0;
		}
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < M; ++i) {
			cin >> chz[j][i];
		}
	}
	int ans = count_chz();
	int time = 0;
	while (count_chz()) {
		time++;
		ans = count_chz();
		melt();
	}
	cout << time << '\n' << ans << '\n';
	return 0;
}