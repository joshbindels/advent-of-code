#include <iostream>
#include <fstream>
#include <set>

using namespace std;

void parseInput(set<int>& out);
long long factorial(int n) {
	long long res = 1;
	for(int i=1; i<=n; i++) {
		res *= i;
	}
	return res;
}

int main() {
	set<int> values;
	parseInput(values);

	int dOneCount = 0;
	int dThreeCount = 0;

	cout << values.size() << endl;

	auto it = values.begin();
	int prevVal = 0;
	int maxVal;
	while(it != values.end()) {
		int d = (*it) - prevVal;
		//cout << *it << " d:" << d << endl;
		if(d > 3) {
			cout << "No available adapter, last value: " << *it << endl;
		}
		if(d == 1) { dOneCount++; }
		if(d == 3) { dThreeCount++; }
		prevVal = *it;
		maxVal = *it;
		it++;
	}
	maxVal += 3;
	dThreeCount++;
	cout << "f: " << factorial(dOneCount) << endl;;
	//cout << "one: " << dOneCount << " three: " << dThreeCount << "onexthree:" << dOneCount*dThreeCount << endl;
    return 0;
}

void parseInput(set<int>& out) {
#ifdef TEST
    ifstream input("test_data.txt");
#else
    ifstream input("input_data.txt");
#endif
    for(string line; getline(input, line);) {
		out.insert(stoi(line));
    }
}
