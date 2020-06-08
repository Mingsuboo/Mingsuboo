#include <iostream>
#include <vector>
#include <stack>

using namespace std;
int N, K;
int A[13][13];
int dir[11];
typedef vector<vector<stack<int>>> VVS;
typedef vector<stack<int>> VS;
pair<int, int> pos[11];
VVS H(13, VS(13));
int dy[5] = {0,0,0,-1,1}, dx[5] = {0,1,-1,0,0};
int trans(int d) {
	if (d == 1) return 2;
	if (d == 2) return 1;
	if (d == 3) return 4;
	if (d == 4) return 3;
}
bool check(int y,int x) {
	if (y<1 || x<1 || y>N || x>N) return false;
	if (H[y][x].size() >= 4) return true;
	return false;
}
bool go() {
	for (int i = 1; i <= K; ++i) {
		stack<int> tmp;
		int y = pos[i].first, x = pos[i].second, d = dir[i];
		int now = H[y][x].top();

		if (now == i) {
			H[y][x].pop();
			tmp.push(now);
		}
		else {
			while (now != i) {
				now = H[y][x].top();
				H[y][x].pop();
				tmp.push(now);
			}
		}
		int ny = y + dy[d], nx = x + dx[d];
		if (ny<1 || nx<1 || ny>N || nx>N || A[ny][nx] == 2) {
			d = trans(d);
			dir[i] = d;
			ny = y + dy[d], nx = x + dx[d];
		}
		if (!(ny<1 || nx<1 || ny>N || nx>N || A[ny][nx] == 2)) {
			if (A[ny][nx] == 0) {
				while (!tmp.empty()) {
					int now = tmp.top();
					tmp.pop();
					H[ny][nx].push(now);
					pos[now].first = ny, pos[now].second = nx;
				}
			}
			else if (A[ny][nx] == 1) {
				stack<int> tmptmp;
				while (!tmp.empty()) {
					int now = tmp.top();
					tmp.pop();
					tmptmp.push(now);
				}
				while (!tmptmp.empty()) {
					int now = tmptmp.top();
					tmptmp.pop();
					H[ny][nx].push(now);
					pos[now].first = ny, pos[now].second = nx;
				}
			}
			if (check(ny, nx)) return true;
		}
		else {
			while (!tmp.empty()) {
				int now = tmp.top();
				tmp.pop();
				H[y][x].push(now);
			}
		}
		
	}
	return false;
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			cin >> A[j][i];
		}
	}
	for (int i = 1; i <= K; ++i) {
		int y, x,d; cin >> y >> x >>d;
		pos[i].first = y; pos[i].second = x;
		H[y][x].push(i);
		dir[i] = d;
	}
	int ans = -1;
	for (int time = 1; time <= 1000; ++time) {
		if (go()) {
			ans = time;
			break;
		}
	}
	cout << ans << '\n';
	return 0;
}