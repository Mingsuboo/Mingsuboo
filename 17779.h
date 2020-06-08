#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int N, A[20][20], cnt[6];
int tmp[20][20];
int ans = 987654321;
void init() {
	for (int i = 0; i < 6; ++i) cnt[i] = 0;
	for (int j = 0; j < 20; ++j)
		for (int i = 0; i < 20; ++i)
			tmp[j][i] = 0;
}
void check(int x, int y, int d1, int d2) {
	init();
	for (int i = 0; i <= d1; ++i) {
		tmp[x + i][y - i] = 5; tmp[x + d2 + i][y + d2 - i] = 5;
	}
	for (int i = 0; i <= d2; ++i) {
		tmp[x + i][y + i] = 5; tmp[x + d1 + i][y - d1 + i] = 5;
	}
	for (int j = x + 1; j < x + d1 + d2; ++j) {
		bool flag = false;
		for (int i = 0; i < N; ++i) {
			if (tmp[j][i] == 5) flag = !flag;
			if (flag) tmp[j][i] = 5;
		}
	}
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			if (tmp[j][i] == 5) {
				cnt[5] += A[j][i];
				continue;
			}
			if (j >= 0 && j < x + d1 && i >= 0 && i <= y) {
				cnt[1] += A[j][i];
				tmp[j][i] = 1;
			}
			else if (j >= 0 && j <= x + d2 && i > y && i < N) {
				cnt[2] += A[j][i];
				tmp[j][i] = 2;
			}
			else if (j >= x + d1 && j < N && i >= 0 && i < y - d1 + d2) {
				cnt[3] += A[j][i];
				tmp[j][i] = 3;
			}
			else if (j > x + d2 && j < N && i >= y - d1 + d2 && i < N) {
				cnt[4] += A[j][i];
				tmp[j][i] = 4;
			}
			else {
				cnt[5] += A[j][i];
				tmp[j][i] = 5;
			}
		}
	}
	int max_num=-1, min_num=987654321;

	for (int i = 1; i < 6; ++i) {
		max_num = max(max_num, cnt[i]);
		min_num = min(min_num, cnt[i]);
	}
	ans = min(ans, max_num - min_num);
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			cin >> A[j][i];
		}
	}
	
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			int x= j, y = i;
			int d1_limit = y, d2_limit = N - y - 1;
			for (int d1 = 1; d1 <= d1_limit; ++d1) {
				for (int d2 = 1; d2 <= d2_limit; ++d2) {
					if (x + d1 + d2 >= N) continue;
					check(x,y,d1,d2);
				}
			}
		}
	}
	cout << ans << '\n';
	return 0;
}