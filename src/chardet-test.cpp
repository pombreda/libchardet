#include <cstdio>
#include <fstream>
#include <streambuf>

#include "chardet.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	for (int idx_file = 1; idx_file < argc; idx_file++) {
		ifstream f(argv[idx_file]);
		std::string str((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
		Chardet::Detector c;
		c.feed(str);
		Chardet::Detector::Stats const * stats = c.get_probabilities();
		printf("Extract: [%s]\n", str.substr(0, 10).c_str());
		printf("Probabilities: for %s\n", argv[idx_file]);
		for (int i = 0; i < stats->size(); i++) {
			auto & kv = (*stats)[i];
			printf(" - %s: %5.3f\n", kv.first, kv.second);
			if (i >= 5) {
				break;
			}
		}
		printf("\n");
	}

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
		for (int i = 0; i < stats->size(); i++) {
			auto & kv = (*stats)[i];
			printf(" - %s: %5.3f\n", kv.first, kv.second);
			if (i >= 10) {
				break;
			}
		}
		printf("\n");
	}

	return 0;
}
