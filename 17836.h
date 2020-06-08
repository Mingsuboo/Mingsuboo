#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
int N, M, T,dist;
int dy[4] = { 0,1,0,-1 }, dx[4] = {1,0,-1,0};
int A[100][100];
int ans = 987654321;

void bfs() {
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));
	A[0][0] = 1;
	int time = 0;
	
	while (!q.empty() && time < T) {

		time++;

		int len = q.size();
		for (int i = 0; i < len; ++i) {
			int y = q.front().first, x = q.front().second; q.pop();
			for (int d = 0; d < 4; ++d) {
				int ny = y + dy[d], nx = x + dx[d];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M || A[ny][nx] == 1) continue;
				if (A[ny][nx] == 2) {
					if (time + dist <= T) ans = min(time + dist, ans);
					A[ny][nx] = 1;
					continue;
				}
				if (ny == N - 1 && nx == M - 1) {
					if (time <= T) ans = min(time, ans);
					return;
				}
				A[ny][nx] = 1;
				q.push(make_pair(ny, nx));
			}
		}
	}
}

int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> T;
	
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < M; ++i) {
			cin >> A[j][i];
			if (A[j][i] == 2) dist = (abs(N - 1 - j) + abs(M - 1 - i));
		}
	}
	bfs();
	if (ans == 987654321) cout << "Fail" << '\n';
	else cout << ans << '\n';
	return 0;
}