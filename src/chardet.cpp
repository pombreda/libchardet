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
}

Detector::~Detector()
{
}

void Detector::feed(char const * data, size_t nbytes)
{
}

void Detector::get_probabilities(std::vector<std::pair<char const *, float>> & stats) const
{
	stats.push_back(std::pair<char const *, float>("utf-8", 0.1));
}

