#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

void EnsureNextSymbolAndSkip(stringstream& stream) {
	if (stream.peek() != '/') {
		//throw exception();
		stringstream ss;
		ss << "expected /, but has: " << char(stream.peek());
		throw runtime_error(ss.str());

	}
	stream.ignore(1);
}

struct Date {
	int year, month, day;
};

Date ParseDate(const string& s) {
	stringstream stream(s);
	Date date;
	stream >> date.year;
	EnsureNextSymbolAndSkip(stream);
	stream >> date.month;
	EnsureNextSymbolAndSkip(stream);
	stream >> date.day;
	return date;
}

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(2) << setfill('0') << date.day << '.'
		<< setw(2) << setfill('0') << date.month << '.'
		<< date.year << endl;
	return stream;
}

int main() {
	string date_str = "2017a01b25";
	try {
		Date date = ParseDate(date_str);
		cout << date;
	}
	catch (exception& ex) {
		cout << "exception happened: " << ex.what();
	}
	return 0;
}