#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int dy[4] = { 0,1,0,-1 }, dx[4] = {1,0,-1,0};
int N, A[25][25], visit[25][25];
vector<int> ans;
void bfs() {
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			if (A[j][i] == 0 || visit[j][i]==1) continue;
			int size = 1;
			visit[j][i] = 1;
			queue<pair<int, int>> q;
			q.push(make_pair(j, i));
			while(!q.empty()) {
				int y = q.front().first, x = q.front().second; q.pop();
				for (int d = 0; d < 4; ++d) {
					int ny = y + dy[d], nx = x + dx[d];
					if (ny < 0 || nx < 0 || ny >= N || nx >= N || visit[ny][nx] == 1) continue;
					if (A[ny][nx] == 0) continue;
					visit[ny][nx] = 1;
					++size;
					q.push(make_pair(ny,nx));
				}
			}
			ans.push_back(size);
		}
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;

	for (int j = 0; j < N; ++j) {
		string tmp;
		cin >> tmp;
		for (int i = 0; i < N; ++i) {
			A[j][i] = tmp[i] - '0';
		}

	}
	bfs();
	cout << ans.size() << '\n';
	sort(ans.begin(), ans.end());
	for (int i = 0; i<int(ans.size()); ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}