#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

template <typename First, typename Second>
pair<First, Second> operator*(const pair<First,Second>& p1, const pair<First,Second>& p2) {
	First first = p1.first * p2.first;
	Second second = p1.second * p2.second;
	return make_pair(first, second);
}

template <typename T>
T sqr(T x) {
	return x * x;
}

template <typename F, typename S>
ostream& operator << (ostream& out, const pair<F, S>& p) {
	return out << '(' << p.first << ',' << p.second << ')';
}

template <typename Collection>
string Join(const Collection& c, char d) {
	stringstream ss;
	bool first = true;
	for (const auto& i : c) {
		if (!first) {
			ss << d;
		}
		first = false;
		ss << i;
	}
	return ss.str();
}


template <typename T>
ostream& operator << (ostream& out, const vector<T>& vi) {
	return out << '[' << Join(vi, ',') << ']';
}

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m) {
	return out << '{' << Join(m, ',') << '}';
}

template <class T>
T Max(T a, T b) {
	if (a > b) return a;
	else return b;
}

int main() {
	cout << sqr(2) << endl;
	cout << sqr(2.5) << endl;

	auto p = make_pair(2, 4.5);
	auto r = sqr(p);
	cout << r.first << " " << r.second << endl;

	// pretty print
	vector<double> vi = { 1.4, 2, 3 };
	cout << vi << endl;
	map<int, double> m = { {1, 2.5}, {3, 4} };
	cout << m << endl;
	vector<vector<int>> v = { {1, 2}, {3, 4} };
	cout << v << endl;

	// avoid ambiguous call
	cout << Max<double>(2, 3.5) << endl;
	cout << max<int>(3.5, 2) << endl;
}