#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
using namespace std;
int N;
char m[50][50];

int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			cin >> m[j][i];
		}
	}
	return 0;
}