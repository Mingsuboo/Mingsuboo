#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
int N,K,board[101][101],L,snake[101][101];
int dy[4] = { -1,0,1,0 }, dx[4] = {0,1,0,-1};

int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for (int i = 0; i < K; ++i) {
		int y, x;
		cin >> y >> x;
		board[y][x] = 2;
	}
	cin >> L;
	deque<pair<int, int>> dq;
	dq.push_back(make_pair(1,1));
	snake[1][1] = 1;
	queue<pair<int, char>> q;
	for (int i = 0; i < L; ++i) {
		int t; char d;
		cin >> t >> d;
		q.push(make_pair(t,d));
	}
	int d = 1;
	int time = 0;
	while (true) {
		++time;
		int y = dq.back().first; int x = dq.back().second;
		int ny = y + dy[d], nx = x + dx[d];
		if (ny<1 || nx <1 || ny>N || nx >N || snake[ny][nx]==1) break;
		snake[ny][nx] = 1;
		dq.push_back(make_pair(ny, nx));

		if (board[ny][nx] != 2) {
			int delete_y = dq.front().first, delete_x = dq.front().second;
			dq.pop_front();
			snake[delete_y][delete_x] = 0;
		}
		else board[ny][nx] = 0;

		if (!q.empty()) {
			if (time == q.front().first) {
				char com = q.front().second;
				q.pop();
				if (com == 'D') {
					d += 1;
					d %= 4;
				}
				else if (com == 'L') {
					d += 3;
					d %= 4;
				}
			}
		}

	}
	cout << time << '\n';
	return 0;
}