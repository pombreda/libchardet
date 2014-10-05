#include <cstdio>

#include "chardet.hpp"

using namespace std;

int main()
{
	vector<string> tests = {
	 "Valid ASCII world",
	 "Valid utf-8 héhé",
	 "Invalid utf-8, valid latin1 \xfe",
	};

	for (auto & test: tests) {
		Chardet::Detector c;
		c.feed(test);
		Chardet::Detector::Stats const * stats = c.get_probabilities();

		printf("Probabilities: for %s\n", test.c_str());
		for (auto & kv : *stats) {
			printf(" - %s: %5.3f\n", kv.first, kv.second);
		}
		printf("\n");
	}

	return 0;
}
