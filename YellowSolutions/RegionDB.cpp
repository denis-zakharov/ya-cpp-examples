#include <map>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs) {
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
		tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
	int result = 0;
	map<Region, int> repetion_count;
	for (const Region& region : regions) {
		result = max(result, ++repetion_count[region]);
	}
	return result;
}
