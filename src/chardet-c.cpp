#include <cstdio>
#include "chardet.hpp"
#include "chardet.h"

using namespace Chardet;

class CChardet {
 public:
	Detector d;
	Detector::Stat const ** stats;
 public:
	CChardet();
	~CChardet();
};

CChardet::CChardet()
{
	stats = NULL;
}

CChardet::~CChardet()
{
	delete [] stats;
}

extern "C" {

chardet_t * chardet_create()
{
	CChardet * c = new CChardet();
	return reinterpret_cast<chardet_t*>(c);
}

void chardet_destroy(chardet_t * that)
{
	delete reinterpret_cast<CChardet*>(that);
}

int chardet_feed(chardet_t * that, char const * data, size_t nbytes)
{
	try {
		reinterpret_cast<CChardet*>(that)->d.feed(data, nbytes);
	}
	catch (...) {
		return -1;
	}
	return 0;
}

int chardet_get_stats(chardet_t * that_, chardet_stat_t const *** results)
{
	CChardet * that = reinterpret_cast<CChardet*>(that_);

	Detector::Stats const * stats = that->d.get_probabilities();

	if (that->stats == NULL) {
		that->stats = new const Detector::Stat*[stats->size()+1]();
	}

	for (int i = 0; i < stats->size(); i++) {
		that->stats[i] = &(*stats)[i];
	}

	that->stats[stats->size()] = NULL;
	*results = (const chardet_stat_t **) that->stats;
	return 0;
}

char const * chardet_stat_get_encoding(chardet_stat_t const * stats)
{
	const Detector::Stat * v = reinterpret_cast<const Detector::Stat*>(stats);
	return v->first;
}

float chardet_stat_get_probability(chardet_stat_t const * stats)
{
	const Detector::Stat * v = reinterpret_cast<const Detector::Stat*>(stats);
	return v->second;
}

} // extern "C"
