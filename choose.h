#ifndef CHOOSE_H
#define CHOOSE_H
#include <algorithm>
#include <vector>
#include "glob.h"

// Used to choose k random numbers in the range [1..n]
//
class Choose
{
private:
	std::vector<LINT> num; // vector of the positions
public:
	Choose(LINT n, LINT k) : num(n) {
		for (LINT i = 0; i < n; ++i) {
			num[i] = i;
		}
		std::shuffle(num.begin(), num.end(), generator);
		num.resize(k);
	};

	LINT pos(LINT i) { return num[i]; };	// returns the i-th position
};
#endif

