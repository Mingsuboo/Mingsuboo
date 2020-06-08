#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
using namespace std;

int N, d, k, c;
map<int, int> m;
void init() {
	for (int i = 1; i <= 3000; ++i) {
		m[i] = 0;
	}
}
int solve(vector<int>& v) {
	deque<int> dq;
	int kind = 1;
	int ans = -1;
	for (int i = 0; i < k; ++i) {
		dq.push_back(v[i]);
		if (m[v[i]] == 0) kind++;
		m[v[i]] = m[v[i]] + 1;
	}
	ans = max(ans, kind);
	for (int i = 0; i < N-1; ++i) {
		int remove = dq.front();
		dq.pop_front();
		m[remove] = m[remove] - 1;
		if (m[remove] == 0) kind--;
		dq.push_back(v[i+k]);
		if (m[v[i + k]] == 0) kind++;
		m[v[i + k]] = m[v[i + k]] + 1;
		ans = max(ans, kind);
	}
	return ans;
}

int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> d >> k >> c;
	vector<int> v(N+(k-1));
	init();
	for (int i = 0; i < N; ++i) {
		cin >> v[i];
	}
	for (int i = 0; i < k - 1; ++i) {
		v[N + i] = v[i];
	}
	m[c] = 1;
	cout << solve(v) << '\n';
	return 0;
}