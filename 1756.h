#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int D, N;
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> D >> N;
	vector<int> v(D);
	queue<int> p;
	for (int i = 0; i < D; ++i) {
		cin >> v[i];
	}
	for (int i = 1; i < D; ++i) {
		v[i] = min(v[i], v[i - 1]);
	}
	for (int i = 0; i < N; ++i) {
		int tmp;
		cin >> tmp;
		p.push(tmp);
	}
	int ans = 0;
	for (int i = D - 1; i >= 0; --i) {
		if (p.empty()) break;
		int now = p.front();
		if (v[i] < now) continue;
		
		else if (v[i] >= now) {
			ans = i+1;
			p.pop();
		}
	}
	if (!p.empty()) cout << '0' << '\n';
	else cout << ans << '\n';
	return 0;
}