#include <iostream>
#include <utility>
#include <map>
#include <vector>
using namespace std;

template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& p1, const pair<First, Second>& p2) {
	First f = p1.first * p2.first;
	Second s = p1.second * p2.second;
	return { f,s };
}

template <typename T>
vector<T> operator*(const vector<T>& rhs, const vector<T>& lhs) {
	vector<T> c;
	for (size_t i = 0; i != rhs.size(); i++) {
		c.push_back(rhs.at(i) * lhs.at(i));
	}
	return c;
}

template <typename K, typename V>
map<K,V> operator*(const map<K, V>& rhs, const map<K, V>& lhs) {
	map<K, V> m;
	for (const auto&[key, value] : rhs) {
		m[key] = value * lhs.at(key);
	}
	return m;
}

template <typename T>
T Sqr(const T& t) {
	return t * t;
}

int main() {
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}