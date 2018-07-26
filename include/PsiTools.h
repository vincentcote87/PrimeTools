#ifndef PSITOOLS_H
#define PSITOOLS_H
#include "Environment.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <climits>
#include <map>
#include "mpreal.h"

#include "s1.h"
#include "s2.h"
#include "s3.h"
#include "s4.h"

typedef uint64_t natural;
typedef long long integer;

mpfr::mpreal getSmallPsi(uint64_t x);
mpfr::mpreal psi_work(uint64_t);
mpfr::mpreal psi(uint64_t);

void psi_setup();
void setupEnvironment();

#endif //PSITOOLS_H

// static const size_t cutoff = 10000000; //4294967295
// static mpfr::mpreal *psiTable;
