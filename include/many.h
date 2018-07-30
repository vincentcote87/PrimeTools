#ifndef MANY_H
#define MANY_H

#include <primesieve.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
#include "mpreal.h"
#include "InterpretClock.h"


static std::vector<long long> prime;
//static long long *prime = nullptr;
//static size_t prime_size = 0;
static primesieve::iterator it;

static std::vector<mpfr::mpreal> theta;
static std::vector<long double> k;
static std::vector<size_t> cur;
static std::vector<long long> lastPrime;

void fillMorePrimes(long long target);
void walkK(const long long x);
mpfr::mpreal sumThetas();
mpfr::mpreal higherPsi(long long x);

#endif //MANY_H
