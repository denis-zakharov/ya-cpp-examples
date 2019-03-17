#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

void printVector(const vector<int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	cout << "Min Max of 2 and 3\n";
	cout << min(2, 3) << endl;
	cout << max(2, 3) << endl;

	vector<int> v{ 3,2,6,5,1,4 };
	sort(begin(v), end(v));
	printVector(v);

	cout << count(begin(v), end(v), 2) << endl;
	cout << count_if(begin(v), end(v), [](int x) {
		return x > 2;
	});
	return 0;
}