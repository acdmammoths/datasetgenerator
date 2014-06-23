#include <cfloat>
#include <cstdlib>
#include <iostream>
#include <random>

// Random number generator
std::mt19937_64 generator(0);

void seed_generator(unsigned seed) {
	generator.seed(seed);
}

double get_uniform_deviate(void) {
	static std::uniform_real_distribution<double> d(DBL_MIN,1.0);
	return d(generator);
}

double get_unit_exponential_deviate(void) {
	static std::exponential_distribution<double> d(1.0);
	return d(generator);
}

void memory_err(void)
{
	std::cout << "A memory allocation error occurred. \n";
	std::exit(EXIT_FAILURE);
}
