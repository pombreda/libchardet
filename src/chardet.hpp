/*!
  \file
  \brief Chardet C++ API
*/

#ifndef CHARDET_HPP
#define CHARDET_HPP

#include <vector>
#include <string>

#include "chardet_pimpl_h.hpp"

namespace Chardet {

class Detector {
 public:
	typedef std::pair<char const *, float> Stat;
	typedef std::vector<Stat> Stats;
 private:
	class impl;
	pimpl<impl> m;

 public:
	Detector();
	~Detector();

 public:
	//! \name Basic Usage
	//! \{

	/*! Feed data into the detector
	 */
	void feed(char const * data, size_t nbytes);
	void feed(std::string const & data) { feed(data.c_str(), data.length()); }

	/*! Retrieve current probabilities
	 */
	const Stats * get_probabilities() const;

	//! \}

 public:
	//! \name Advanced Usage
	//! \{
	//! \TODO design
	//! \}

};

} // Chardet::

#endif // CHARDET_HPP
