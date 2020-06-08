#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, m, M, T, R;
int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> m >> M >> T >> R;
	
	if (M - m < T) {
		cout << -1 << '\n';
		return 0;
	}
	else {
		int ans = 0;
		int now = m;
		int time = 0;
		while (time < N) {
			if (now + T <= M) {
				now += T;
				time++;
			}
			else {
				now -= R;
				now = max(now, m);
			}
			ans++;
		}
		cout << ans << '\n';
	}
}