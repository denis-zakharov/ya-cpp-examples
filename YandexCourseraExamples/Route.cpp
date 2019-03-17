#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Route {
public:
	Route(const string& new_src, const string& new_dst) {
		source = new_src;
		destination = new_dst;
		UpdateLength();
	}
	string GetSource() const { return source; }
	string GetDestination() const { return destination; }
	int GetLength() { return length; }
	void SetSource(const string& new_source) {
		source = new_source;
		UpdateLength();
	}
	void SetDestination(const string& new_dst) {
		destination = new_dst;
		UpdateLength();
	}
	~Route() {
		for (const string& entry : compute_distance_log) {
			cout << entry << "\n";
		}
		cout << "Destructed\n";
	}
private:
	void UpdateLength() {
		length = ComputeDistance();
		compute_distance_log.push_back(source + " - " + destination);
	}
	int ComputeDistance() {
		size_t sourceSize = source.size();
		size_t dstSize = destination.size();
		if (sourceSize > dstSize) return sourceSize;
		else if (dstSize > sourceSize) return dstSize;
		else return sourceSize + dstSize;
	}
	string source;
	string destination;
	int length;
	vector<string> compute_distance_log;
};