#ifndef MOBIUS_H
#define MOBIUS_H
#include "Environment.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <climits>
#include "mpreal.h"

long long mobius(long long);
long long mobius_work(long long);
void mobius_setup();

extern const uint64_t mobiusCutoff;
extern long long *mobiusTable;

#endif
