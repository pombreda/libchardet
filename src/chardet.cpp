/*!
  \file
  \brief Chardet Implementation Entry Point

*/

#include <cstring>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

#include <cstdio>

#if defined(HAVE_ICONV_H)
# include <iconv.h>
#endif

#if defined(HAVE_ICU)
# include <unicode/ucnv.h>
#endif

#include "chardet.hpp"
#include "chardet_pimpl_impl.hpp"

using namespace std;
using namespace Chardet;


class Detector::impl {
 public:
	Stats stats;
	unordered_map<string, float> probas;
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

#if defined(HAVE_ICU)
	int n_convs = ucnv_countAvailable();
	for (int idx_conv = 0; idx_conv < n_convs; idx_conv++) {
		char const * name = ucnv_getAvailableName(idx_conv);
		probas[name] = 0.01;
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

#if defined(HAVE_ICU)
	{
		int n_convs = ucnv_countAvailable();
		for (int idx_conv = 0; idx_conv < n_convs; idx_conv++) {
			char const * name = ucnv_getAvailableName(idx_conv);

			if (strstr(name, "2022") != NULL) {
				continue;
			}

			UErrorCode errorCode = U_ZERO_ERROR;
			UConverter *conv = ucnv_open(name, &errorCode);
			if (conv == NULL) {
				continue;
			}

			int32_t tcap = nbytes*4;
			char * target = new char[tcap];
			int32_t scap = nbytes;
			char const * src = data;

			ucnv_convert("UTF-32", name, target, tcap, src, scap, &errorCode);

			delete [] target;

			ucnv_close(conv);

			if (errorCode == U_ZERO_ERROR) {
				m->probas[name] = 1.0;
			}
		}
	}
#endif

#if defined(HAVE_ICONV_H)
	for (char const * encoding: m->iconv_encodings) {
		iconv_t cd = iconv_open(encoding, "UTF-8");
		char * addr = const_cast<char*>(data);
		size_t len = nbytes;
		char out_buf[3200];
		char * outptr;
		size_t outlen;
		size_t block = 0;
		size_t done = 0;
		while (done < nbytes) {
			size_t todo = len = min(nbytes - done, sizeof(out_buf));
			addr = const_cast<char*>(&data[done]);
			outptr = &out_buf[0];
			outlen = sizeof(out_buf);

			//fprintf(stderr, "%.32s %s block=%zu/%zu/%zu %p",
			// addr, encoding, block, len, nbytes, addr);

			res = iconv(cd, &addr, &len, &outptr, &outlen);

			//fprintf(stderr, " res=%d after=%zu outlen=%zu\n",
			// res, len, outlen);
			//if (res == -1) {
			//	perror("pouet");
			//}

			if (res == -1) {
				m->probas[encoding] = 0.0;
				break;
			}
			else {
				m->probas[encoding] = 0.5;
			}
			done += (todo-len);
			block++;
		}
		if (len == 0) {
			m->probas[encoding] = 1.0;
		}
		iconv_close(cd);
	}
#endif

	int i = 0;
	for (auto & kv : m->probas) {
		m->stats[i].first = kv.first.c_str();
		m->stats[i].second = kv.second;
		i++;
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
