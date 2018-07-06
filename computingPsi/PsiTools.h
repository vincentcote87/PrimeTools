#ifndef PSITOOLS_H
#define PSITOOLS_H
#include <iostream>
#include <cmath>
#include <iomanip>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <climits>
#include "B2.hpp"
#include "../include/Primetools.h"

typedef uint64_t natural;
typedef long long integer;
long double T(long double);
long double psi_work(uint64_t);
long double psi(uint64_t);
long double S1(uint64_t, uint64_t);
long double S2(uint64_t, uint64_t);
long double S3(uint64_t, uint64_t);
long long S3_B(uint64_t, uint64_t, uint64_t);
long double S3_A(uint64_t, uint64_t, uint64_t);
long double S4(uint64_t, uint64_t);
long long mobius(long long);
long long mobius_work(long long);
void mobius_setup();
void psi_setup();
void setupEnvironment();
#endif //PSITOOLS_H

B2Class B2;
const long double PI = 3.141592653589793238462643383279L;
const int J = 5;

const uint64_t mobiusCutoff = 3000000;
long long *mobiusTable;

const size_t cutoff = 10000000; //4294967295
long double *psiTable;
