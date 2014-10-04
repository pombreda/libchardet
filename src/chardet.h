/*!
  \file
  \brief Chardet C API
*/

#ifndef LIBCHARDET_CHARDET_H
#define LIBCHARDET_CHARDET_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <string.h>

struct chardet;
struct chardet_stat;

typedef struct chardet chardet_t;
typedef struct chardet_stat chardet_stat_t;


//! Create a chardet detector
chardet_t * chardet_create();

//! Destroy a chardet detector
void chardet_destroy(chardet_t * detector);

//! Feed a detector with data
int chardet_feed(chardet_t * detector, char const * data, size_t nbytes);

/*! Get the probabilities of a character detector

  \param[out] results NULL-terminated pointer list of stats

*/
int chardet_get_stats(chardet_t *, chardet_stat_t const *** results);


char const * chardet_stat_get_encoding(chardet_stat_t const * stats);
float chardet_stat_get_probability(chardet_stat_t const * stats);


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // LIBCHARDET_CHARDET_H
