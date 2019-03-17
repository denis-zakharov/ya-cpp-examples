#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;

struct Duration {
	int hour;
	int min;
	Duration(int h = 0, int m = 0) {
		int total = h * 60 + m;
		hour = total / 60;
		min = total % 60;
	}
};

Duration ReadDuration(istream& stream) {
	int h = 0;
	int m = 0;
	stream >> h;
	stream.ignore(1);
	stream >> m;
	return Duration{ h, m };
}

void PrintDuration(ostream& stream, const Duration& duration) {
	stream << setfill('0');
	stream << setw(2) << duration.hour << ':'
		<< setw(2) << duration.min;
}

ostream& operator<<(ostream& stream, const Duration& duration) {
	stream << setfill('0');
	stream << setw(2) << duration.hour << ':'
		<< setw(2) << duration.min;
	return stream;
}

istream& operator>>(istream& stream, Duration& duration) {
	stream >> duration.hour;
	stream.ignore(1);
	stream >> duration.min;
	return stream;
}

Duration operator+(const Duration& lhs, const Duration& rhs) {
	return Duration(lhs.hour + rhs.hour, lhs.min + rhs.min);
}

void PrintVector(const vector<Duration>& v) {
	for (const auto& d : v) {
		cout << d << ' ';
	}
	cout << endl;
}

bool operator<(const Duration& lhs, const Duration& rhs) {
	if (lhs.hour == rhs.hour) {
		return lhs.min < rhs.min;
	}
	return lhs.hour < rhs.hour;
}

int main() {
	stringstream dur_ss("11:40");
	Duration dur1 = ReadDuration(dur_ss);
	Duration dur2;
	PrintDuration(cout, dur1);
	cout << endl;

	// IO operators overloading
	stringstream dur_ss2("21:18");
	dur_ss2 >> dur2;
	cout << dur2 << endl;
	Duration dur3 = dur1 + dur2;
	cout << dur3 << endl;
	vector<Duration> v{ dur1,dur3,dur2 };
	PrintVector(v);
	sort(begin(v), end(v), [](const Duration& lhs, const Duration& rhs) {
		if (lhs.hour == rhs.hour) {
			return lhs.min < rhs.min;
		}
		return lhs.hour < rhs.hour;
	});
	PrintVector(v);

	cout << boolalpha << (dur1 < dur2) << endl;

	// operators in structs
	ifstream input("runner.txt");
	Duration worst;
	map<Duration, string> all;
	if (input) {
		Duration dur;
		string name;
		while (input >> dur >> name) {
			if (worst < dur) {
				worst = dur;
			}
			all[dur] += (name + " ");
		}
	}

	ofstream out("result.txt");
	for (const auto& durationNames : all) {
		out << durationNames.first << '\t' << durationNames.second << endl;
	}
	
	cout << "Worst runner: " << all[worst] << endl;
	return 0;
}