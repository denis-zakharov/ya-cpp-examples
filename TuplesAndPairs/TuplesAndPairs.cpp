#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <utility>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

struct Date {
	int year;
	string month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	// incorrent: months are compared alphanumerically
	return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day); // compare tuples
}

class Cities {
public:
	tuple<bool, string> FindCountry(const string& city) const {
		if (city_to_country.count(city) == 1) {
			return { true, city_to_country.at(city) }; // const method at throws exception
		}
		else if (ambiguous_cities.count(city) == 1) {
			return { false, "ambiguous" };
		}
		else {
			return { false, "not found" };
		}
	}
private:
	map<string, string> city_to_country;
	set<string> ambiguous_cities;
};

int main()
{
	cout << boolalpha << (Date{ 1999, "Dec", 13 } < Date{ 1999, "Jan", 9 });

	tuple<int, string, bool> t(7, "C++", true);
	tuple tt(7, "C++", true); // project - properties - c++ - language - standard c++17
	auto t2 = make_tuple(7, "C++", true); // tie() returns a tuple of references - it cannot be used here because 7 and true are primitive types
	cout << get<1>(t2) << endl; // use structs if you work with fields!

	pair<int, string> p(1, "one");
	pair pp(2, "two");
	auto p2 = make_pair(3, "three");
	cout << p.first << ':' << p.second << endl;

	map<int, string> digits = { {1, "one"} };
	for (const auto& item : digits) {
		// map iterator creates pairs!
		cout << item.first << ':' << item.second << endl;
	}
	for (const auto&[key, value] : digits) {
		// structured binding
		cout << key << ':' << value << endl;
	}

	Cities cities;
	// variant 1
	//auto ctup = cities.FindCountry("Moscow");
	//cout << get<0>(ctup) << endl;
	// better
	//bool success; string msg;
	//tie(success, msg) = cities.FindCountry("Moscow");
	// even better c++17
	auto [success, msg] = cities.FindCountry("Moscow");
	cout << success << endl;
	return 0;
}
