#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
int N, M;
priority_queue<int, vector<int>, greater<int>> pq;
map<int, vector<int>> order;
map<int, int> cnt;
void init() {
	for (int i = 1; i <= 32000; ++i) {
		cnt[i] = 0;
	}
}
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int x, y;
		cin >> x >> y;
		order[x].push_back(y);
		cnt[y] = cnt[y] + 1;
	}
	for (int i = 1; i <= N; ++i) {
		if (cnt[i] == 0) pq.push(i);
	}
	while (!pq.empty()) {
		int now = pq.top();
		pq.pop();
		cout << now << ' ';
		if (order.find(now) == order.end()) continue;
		for (int i = 0; i < order[now].size(); ++i) {
			int next = order[now][i];
			cnt[next] = cnt[next] - 1;
			if (cnt[next] == 0) pq.push(next);
		}
	}
	cout << '\n';
	return 0;
}