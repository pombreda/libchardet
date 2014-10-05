/*!
  \file
  \brief Chardet Implementation Entry Point

*/

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

#include <cstdio>

#if defined(HAVE_ICONV_H)
# include <iconv.h>
#endif

#include "chardet.hpp"
#include "chardet_pimpl_impl.hpp"

using namespace std;
using namespace Chardet;


class Detector::impl {
 public:
	Stats stats;
	unordered_map<char const *, float> probas;
#if defined(HAVE_ICONV_H)
	vector<char const *> iconv_encodings;
#endif
 public:
	impl();
	~impl();
};

Detector::impl::impl()
 : stats()
#if defined(HAVE_ICONV_H)
 , iconv_encodings(ICONV_ENCODINGS)
#endif
{

#if defined(HAVE_ICONV_H)
	for (auto & e: iconv_encodings) {
		probas[e] = 0.001;
	}
#endif

	probas["UTF-8"] = 0.01;
	probas["ASCII"] = 0.01;
	probas["WINDOWS-1252"] = 0.5;
	stats.resize(probas.size());
}

Detector::impl::~impl()
{
}

Detector::Detector()
{

}

Detector::~Detector()
{
}

void Detector::feed(char const * data, size_t nbytes)
{
	int res;

#if defined(HAVE_ICONV_H)
	for (char const * encoding: m->iconv_encodings) {
		iconv_t cd = iconv_open(encoding, "UTF-8");
		char * addr = const_cast<char*>(data);
		size_t len = nbytes;
		char out_buf[32];
		char * outptr;
		size_t outlen;
		while (len > 0) {
			outptr = &out_buf[0];
			outlen = sizeof(out_buf);
			res = iconv(cd, &addr, &len, &outptr, &outlen);
			if (res == -1) {
				m->probas[encoding] = 0.0;
				break;
			}
		}
		if (len == 0) {
			m->probas[encoding] = 1.0;
		}
		iconv_close(cd);
	}
#endif

	int i = 0;
	for (auto & kv : m->probas) {
		m->stats[i++] = kv;
	}

	auto by_decreasing_proba = [](Stat const & a, Stat const & b) -> bool
	 {
		 if (a.second == b.second) {
			 if (string("ASCII") == a.first) {
				 return true;
			 }
			 else if (string("UTF-8") == a.first) {
				 return true;
			 }
		 }
		 return a.second > b.second;
	 };

	sort(m->stats.begin(), m->stats.end(), by_decreasing_proba);

}

const Detector::Stats * Detector::get_probabilities() const
{
	return &const_cast<Detector*>(this)->m->stats;
}
