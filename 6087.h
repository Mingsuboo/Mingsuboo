#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int W, H, dy[4] = { 0,1,0,-1 }, dx[4] = {1,0,-1,0};
char A[100][100];
int visit[100][100];
pair<int, int> start,End;
bool check(int di, int d) {
	if (di == 0 && d == 2) return true;
	else if (di == 1 && d == 3) return true;
	else if (di == 2 && d == 0) return true;
	else if (di == 3 && d == 1) return true;
	return false;
}
void bfs() {
	memset(visit, -1, sizeof(visit));
	queue<vector<int>> q;
	int y = start.first, x = start.second;
	visit[y][x] = 0;
	for (int d = 0; d < 4; ++d) {
		int ny = y + dy[d], nx = x + dx[d];
		if (ny < 0 || nx < 0 || ny >= H || nx >= W || A[ny][nx] == '*') continue;
		vector<int> tmp = {ny,nx,d};
		q.push(tmp);
		visit[ny][nx] = 0;
	}
	while (!q.empty()) {
		vector<int> now = q.front(); q.pop();
		int y = now[0], x = now[1], di = now[2];
		for (int d = 0; d < 4; ++d) {
			if (check(di, d)) continue;
			int cnt = visit[y][x];
			int ny = y + dy[d], nx = x + dx[d];
			if (ny < 0 || nx < 0 || ny >= H || nx >= W || A[ny][nx]=='*') continue;
			if (di != d) cnt++;
			if (visit[ny][nx] < cnt && visit[ny][nx]!=-1) continue;
			visit[ny][nx] = cnt;
			vector<int> tmp = { ny,nx,d };
			q.push(tmp);
		}
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> W >> H;
	bool flag = false;
	for (int j = 0; j < H; ++j) {
		for (int i = 0; i < W; ++i) {
			cin >> A[j][i];
			if (A[j][i] == 'C' && flag == false) {
				start.first = j;
				start.second = i;
				flag = true;
			}
			else if (A[j][i] == 'C' && flag == true) {
				End.first = j;
				End.second = i;
			}
			
		}
	}
	bfs();
	cout << visit[End.first][End.second] << '\n';
	return 0;
}