#include <algorithm>
#include <vector>
using namespace std;
class FunctionPart {
public:
	FunctionPart(char new_op, double new_val) {
		op = new_op;
		val = new_val;
	}
	double Apply(double src_val) const {
		if (op == '+') {
			return src_val + val;
		}
		else {
			return src_val - val;
		}
	}
	void Invert() {
		if (op == '+') {
			op = '-';
		}
		else {
			op = '+';
		}
	}
private:
	char op;
	double val;
};

class Function {
public:
	void AddPart(char op, double val) {
		parts.push_back({ op, val });
	}
	double Apply(double val) {
		for (const FunctionPart& part : parts) {
			val = part.Apply(val);
		}
		return val;
	}
	void Invert() {
		for (FunctionPart& part : parts) {
			part.Invert();
		}
		reverse(begin(parts), end(parts));
	}
private:
	vector<FunctionPart> parts;
};

struct Image
{
	double quality;
	double freshness;
	double rating;
};

struct Params
{
	double a;
	double b;
	double c;
};
