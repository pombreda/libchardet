/*!
  \file
  \brief Chardet Implementation Entry Point

*/

#include <string>
#include <stdexcept>

#include "chardet.hpp"

using namespace std;
using namespace Chardet;

Detector::Detector()
{
	stats.clear();
	stats.push_back(std::pair<char const *, float>("utf-8", 0.1));
}

Detector::~Detector()
{
}

void Detector::feed(char const * data, size_t nbytes)
{
}

const Detector::Stats * Detector::get_probabilities() const
{
	return &stats;
}
