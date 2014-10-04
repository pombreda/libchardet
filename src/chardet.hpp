/*!
  \file
  \brief Chardet C++ API
*/

#ifndef CHARDET_HPP
#define CHARDET_HPP

#include <vector>
#include <string>

namespace Chardet {

class Detector {
 private:

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
	void get_probabilities(std::vector<std::pair<char const *, float>> & stats) const;

	//! \}

 public:
	//! \name Advanced Usage
	//! \{
	//! \TODO design
	//! \}

};

} // Chardet::

#endif // CHARDET_HPP
