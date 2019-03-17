struct Day {
	int value;
	explicit Day(int new_val) {
		value = new_val;
	}
};

struct Month {
	int value;
	explicit Month(int new_val) {
		value = new_val;
	}
};

struct Year {
	int value;
	explicit Year(int new_val) {
		value = new_val;
	}
};

struct Date{
	int day;
	int month;
	int year;
	Date(Day new_day, Month new_month, Year new_year) {
		day = new_day.value;
		month = new_month.value;
		year = new_year.value;
	}
};