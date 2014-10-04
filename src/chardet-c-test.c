#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "chardet.h"

int main() {
	int res;
	chardet_t * detector = chardet_create();

	char const * s = "Hello World";
	res = chardet_feed(detector, s, strlen(s));
	assert(res == 0);

	chardet_stat_t const ** stats;

	chardet_get_stats(detector, &stats);

	printf("Probabilities:\n");

	for (int i = 0; stats[i] != NULL; i++) {
		char const * encoding = chardet_stat_get_encoding(stats[i]);
		float proba = chardet_stat_get_probability(stats[i]);
		printf(" - %s: %5.3f\n", encoding, proba);
	}

	chardet_destroy(detector);
}
