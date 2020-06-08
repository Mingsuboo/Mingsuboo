#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int N, M,V, A[1001][1001],visit[1001];
void dfs(int start) {
	cout << start << ' ';
	for (int i = 1; i <= N; ++i) {
		if (visit[i] == 1 || A[start][i]==0) continue;
		visit[i] = 1;
		dfs(i);
	}
}
void bfs(int start) {
	memset(visit, 0, sizeof(visit));
	queue<int> q;
	q.push(start);
	visit[start] = 1;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		cout << now << ' ';
		for (int i = 1; i <= N; ++i) {
			if (visit[i] == 1 || A[now][i] == 0)continue;
			visit[i] = 1;
			q.push(i);
		}
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> V;
	for (int i = 0; i < M; ++i) {
		int y, x;
		cin >> y >> x;
		A[y][x] = 1;
		A[x][y] = 1;
	}
	visit[V] = 1;
	dfs(V);
	cout << '\n';
	bfs(V);
	cout << '\n';
	return 0;
}