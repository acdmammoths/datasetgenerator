#ifndef GLOB_H
#define GLOB_H
#include <cfloat>
#include <random>
// Some global declarations

// g++ all the occurrences of strings functions were modified adding the :: 
#define IBM_VERSION "Version dated July 22, 1997"
#define VERSION "Version 20140623"

typedef int LINT;
typedef double FLOAT;
typedef double DOUBLE;

// useful types
typedef LINT Item;
typedef LINT Cid;

void seed_generator(unsigned seed);

double get_uniform_deviate(void);

double get_unit_exponential_deviate(void);

void memory_err(void);

extern std::mt19937_64 generator;

#endif

