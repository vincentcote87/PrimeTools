#ifndef S2_H
#define S2_H
#include "Environment.h"
#include "B2.h"
#include "mobius.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <climits>
#include "mpreal.h"
#include "PsiTools.h"

size_t idealT_tableSize(uint64_t);
static mpfr::mpreal* T_table;
void Tsetup(uint64_t);
mpfr::mpreal Tbrute(uint64_t);
mpfr::mpreal T(uint64_t);
mpfr::mpreal fastT(uint64_t);
mpfr::mpreal Terror(uint64_t);
mpfr::mpreal S2(uint64_t, mpfr::mpreal);

static B2Class B2;

static int J = 10;

static size_t T_tableSize = 0;

#endif


