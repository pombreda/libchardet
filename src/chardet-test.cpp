#include <cstdio>

#include "chardet.hpp"

using namespace std;

int main()
{
	Chardet::Detector c;

	c.feed("Hello World");

	std::vector<std::pair<char const *, float>> stats;

	c.get_probabilities(stats);

	printf("Probabilities:\n");
	for (auto & kv : stats) {
		printf(" - %s: %5.3f\n", kv.first, kv.second);
	}

	return 0;
}
