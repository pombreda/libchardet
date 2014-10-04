#include <cstdio>

#include "chardet.hpp"

using namespace std;

int main()
{
	Chardet::Detector c;

	c.feed("Hello World");

	Chardet::Detector::Stats const * stats = c.get_probabilities();

	printf("Probabilities:\n");
	for (auto & kv : *stats) {
		printf(" - %s: %5.3f\n", kv.first, kv.second);
	}

	return 0;
}
