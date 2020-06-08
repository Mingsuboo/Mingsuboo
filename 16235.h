#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int N, M, K;
int A[11][11];
int farm[11][11];
int avail[11][11];
int dy[8] = { -1,-1,-1,0,1,1,1,0 }, dx[8] = {-1,0,1,1,1,0,-1,-1};
vector<int> trees[11][11];

void springandsummer() {
	
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			vector<int> tmptmp;
			int tmp = 0;
			sort(trees[j][i].begin(), trees[j][i].end());
			for (int k = 0; k < trees[j][i].size(); ++k) { //pq 이용해서 어린 순서대로 빼내는 
				int now = trees[j][i][k];
				if (now <= farm[j][i]) { // 양분섭취가 가능할때
					farm[j][i] -= now;
					++now;

					if ((now % 5) == 0) { //번식이 가능한 애들 횟수 세는 코드
						avail[j][i]++;
					}

					tmptmp.push_back(now);
				}
				else {
					tmp += (now / 2);
				}
			}
			trees[j][i] = tmptmp;
			farm[j][i] += tmp;
		}
	}
}
void fall() {
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			int cnt = avail[j][i];
			for (int c = 0; c < cnt; ++c) {
				for (int d = 0; d < 8; ++d) {
					int ny = j + dy[d], nx = i + dx[d];
					if (ny<1 || nx <1 || ny>N || nx>N) continue;
					trees[ny][nx].push_back(1);
				}
			}
			avail[j][i] = 0;
		}
	}
}
void winter() {
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			farm[j][i] += A[j][i];
		}
	}
}
int count() {
	int sum = 0;
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			sum += trees[j][i].size();
		}
	}
	return sum;
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> K;
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			int tmp; cin >> tmp;
			A[j][i] = tmp;
			farm[j][i] = 5;
		}
	}
	for (int i = 0; i < M; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		trees[x][y].push_back(z);
	}
	for (int k = 0; k < K; ++k) {
		springandsummer();
		fall();
		winter();
	}
	cout << count() << '\n';
	return 0;
}