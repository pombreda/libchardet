import warnings

cdef extern from "chardet.h":
	ctypedef void chardet_t
	cdef chardet_t * chardet_create()
	cdef void chardet_destroy(chardet_t * chardet)
	cdef int chardet_feed(chardet_t * chardet, char* data, size_t nbytes)
	cdef int chardet_get_stats(chardet_t * chardet, void*** results)
	cdef char* chardet_stat_get_encoding(void* stats)
	cdef float chardet_stat_get_probability(void* stats)

cdef class Detector:
	cdef chardet_t * detector;

	def __init__(self):
		self.detector = chardet_create()

	def __del__(self):
		chardet_destroy(self.detector)

	def feed(self, data):
		cdef char *msg = data;
		cdef size_t nbytes = len(data)
		cdef int res = chardet_feed(self.detector, msg, nbytes)
		cdef void** results = NULL
		cdef void * result = NULL
		cdef char * encoding = NULL
		cdef float score = 0
		res = chardet_get_stats(self.detector, &results)
		assert res == 0
		ret = []
		i = 0
		while True:
			result = results[i]
			if result == NULL:
				break
			encoding = chardet_stat_get_encoding(result)
			score = chardet_stat_get_probability(result)
			ret.append((encoding, score))
			i += 1
		return ret
