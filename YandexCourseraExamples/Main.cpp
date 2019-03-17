#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Route.cpp"
#include "ExplicitDate.cpp"
#include "Function.cpp"
using namespace std;

struct Lecture {
	string title = "C++"; // a default value
	int duration;
	string author;
};

void PrintLecture(const Lecture& lecture) {
	cout << "Title: " << lecture.title <<
		", duration: " << lecture.duration <<
		", author: " << lecture.author << "\n";
}

void PrintRoute(const Route& route) {
	cout << route.GetSource() << " - " <<
		route.GetDestination() << endl;
}

void PrintRoutes(const vector<Route>& routes) {
	for (const Route& r : routes) {
		PrintRoute(r);
	}
}

void ReverseRoute(Route& route) {
	string old_source = route.GetSource();
	string old_dst = route.GetDestination();
	route.SetSource(old_dst);
	route.SetDestination(old_source);
}

vector<int> GetNumbers(bool is_empty) {
	if (is_empty) {
		return {};
	}
	else {
		return { 8,6,9,6 };
	}
}

Function MakeWeightFunction(const Params& params, const Image& image) {
	Function function;
	function.AddPart('-', image.freshness * params.a + params.b);
	function.AddPart('+', image.rating * params.c);
	return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
	Function function = MakeWeightFunction(params, image);
	return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params, const Image& image, double weight) {
	Function function = MakeWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
}

void PrintVectorReverse(const vector<int>& v, int m, int n) {
	for (size_t k = v.size(); k > m + n; k--) {
		size_t i = k - m - 1;
		cout << v[i] << " ";
	}
	cout << endl;
}

int main() {
	cout << "Hello Empty!\n";
	Lecture l{ "Title", 100, "Denis" };
	PrintLecture(l);
	Route route_capitals("Moscow", "Peter");
	PrintRoute(route_capitals);
	ReverseRoute(route_capitals);
	PrintRoute(route_capitals);
	PrintRoute(Route("Src", "Dst"));
	PrintRoute({ "Tagil", "Vladivostok" });

	vector<Route> routes;
	routes.push_back({ "Zvenigorod", "Istra" });
	routes.push_back(Route("Town1", "Town2"));
	PrintRoutes(routes);

	Date date(Day(13), Month(10), Year(2018)); // using explicit constructors to avoid Date(10,1999,12)

	Image image = { 10, 2, 6 };
	Params params = { 4, 2, 6 };
	cout << ComputeImageWeight(params, image) << endl; // 36

	vector<int> vint{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<int> vempty;
	vector<int> vone{ 1 };
	PrintVectorReverse(vint, 2, 3);
	PrintVectorReverse(vempty, 2, 3);
	PrintVectorReverse(vone, 0, 0);
	PrintVectorReverse(vone, 0, 1);
	PrintVectorReverse(vone, 1, 0);

	map<string, int> m {{"one", 1}};
	int from_map = m["one"];
	m["one"]++;
	cout << "FROM MAP: " << from_map << endl;
	cout << "MAP ONE: " << m["one"] << endl;
	return 0;
}