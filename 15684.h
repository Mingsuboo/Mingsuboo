#include <iostream>
#include <vector>
bool flag = false;
using namespace std;
int N, M, H;
int lad[31][11];
bool go() {
	for (int i = 1; i <= N; ++i) {
		int idx = 0;
		int i_tmp = i;
		while (idx < H) {
			idx++;
			if (lad[idx][i_tmp] == 1) i_tmp++;
			else if (lad[idx][i_tmp] == 2) i_tmp--;
		}
		if (i_tmp != i) return false;
	}
	return true;
}
void dfs(int limit, int cnt, int start_x, int start_y) {
	if (cnt == limit) {
		if (go()) flag = true;
		return;
	}
	for (int j = start_y; j <= H; ++j) {
		for (int i = 0; i < N; ++i) {
			if (lad[j][i] != 0 || lad[j][i+1]!=0) continue;
			lad[j][i] = 1, lad[j][i + 1] = 2;
			dfs(limit, cnt + 1,i, j);
			if (flag) return;
			lad[j][i] = 0, lad[j][i + 1] = 0;
		}
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> H;
	int ans = -1;
	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		lad[a][b] = 1, lad[a][b + 1] = 2;
	}
	for (int h = 0; h <= 3; ++h) {
		dfs(h, 0, 1, 1);
		if (flag) {
			ans = h;
			break;
		}
	}
	cout << ans << '\n';
	return 0;
}