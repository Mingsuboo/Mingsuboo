#include <iostream>
#include <vector>

using namespace std;

int function() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int sum_ = 0;
	for (int i = 0; i < 5; ++i) {
		
		int tmp;
		cin >> tmp;
		if (tmp < 40) tmp = 40;
		sum_ += tmp;
	}
	sum_ /= 5;
	cout << sum_  << '\n';
}