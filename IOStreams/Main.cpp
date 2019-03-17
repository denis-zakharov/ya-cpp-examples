#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*
istream -- cin
ostream -- cout
iostream -- both

File stream subclasses:
ifstream - input file stream
ofstream - output file stream
fstream -- both
*/

void Print(const vector<string>& names, const vector<double>& values, int width) {
	for (const auto& n : names) {
		cout << setw(width) << n << ' ';
	}
	cout << endl;
	cout << fixed << setprecision(2);
	for (const auto& v : values) {
		cout << setw(width) << v << ' ';
	}
	cout << endl;
}

int main() {
	cout << "Hello Empty!\n";

	ifstream input("hello.txt");
	ifstream date_ifstream("date.txt");

	string line;
	if (input.is_open()) {
		while (getline(input, line)) {
			cout << line << endl;
		}
		cout << "done!" << endl;
	}
	else {
		cout << "error!" << endl;
	}

	int year, month, day;
	if (date_ifstream) {
		date_ifstream >> year;
		date_ifstream.ignore(1);
		date_ifstream >> month;
		date_ifstream.ignore(1);
		date_ifstream >> day;
		date_ifstream.ignore(1);
	}
	cout << year << ' ' << month << ' ' << day << endl;

	// read till the separator
	ifstream date2_ifstream("date.txt");
	while (getline(date2_ifstream, line, '-')) {
		cout << line << " ";
	}
	cout << endl;

	// write to a file
	const string path = "output.txt";
	ofstream output(path);
	output << "hello" << endl;
	output.close();

	output = ofstream(path, ios::app);
	output << " world!" << endl;

	// formatted output <iomanip>
	vector<string> names{ "a", "b", "c" };
	vector<double> values{ 5,0.01,0.000005 };

	cout << fixed << setprecision(2); // fixed width
	cout << setw(10); // the field's width, it is reset every time
	cout << setfill('.'); // the padding char between columns
	cout << left; // left align
	Print(names, values, 10);
	return 0;
}