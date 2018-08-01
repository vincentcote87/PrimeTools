#include "gtest/gtest.h"
#include "../include/Primetools.h"
#include "../include/PsiTools.h"
#include "../include/s2.h"

#include <iostream>

TEST (B2Test, bernoulliSize) {
  EXPECT_EQ(B2.size(), 12);
}

TEST (B2Test, bernoulliValue_of_2) {
  mpfr::mpreal::set_default_prec(192);
  EXPECT_TRUE(B2[1] - 1.0/6.0 <= 0.000000000001);
}

TEST (B2Test, bernoulliValue_of_10) {
  EXPECT_TRUE(B2[4] - 5.0/66.0 <= 0.000000000001);
}

//
// void Tsetup(uint64_t x) {
// 	std::cout << "Running Tsetup...";
// 	mpfr::mpreal x_u = (mpfr::mpreal) (x);
// 	T_table = new mpfr::mpreal[x + 1];
// 	size_t oldSize = T_tableSize;
// 	T_tableSize = x + 1;
// 	mpfr::mpreal sum;
// 	if (oldSize) {
// 		sum = T_table[oldSize - 1];
// 	} else {
// 		sum = 0.0;
// 	}
// 	size_t index;
// 	if (oldSize) {
// 		index = oldSize;
// 	} else {
// 		index = 1;
// 	}
// 	for (mpfr::mpreal i = index; i <= x_u; ++i) {
// 		sum += log(i, MPFR_RNDN);
// 		T_table[index++] = sum;
// 	}
// 	std::cout << "Done" << std::endl;
// }
//
// size_t idealT_tableSize(uint64_t x) {
// 	return x;
// }
//
// mpfr::mpreal Tbrute(uint64_t n) {
// 	mpfr::mpreal sum = 0.0;
// 	mpfr::mpreal N = n;
// 	for (mpfr::mpreal i = 1; i <= N; ++i) {
// 		sum += log(i, MPFR_RNDN);
// 	}
// 	return sum;
// }
//
//
// mpfr::mpreal Terror(uint64_t N) {
// 	mpfr::mpreal f3 = pow(mpfr::mpreal{N}, mpfr::mpreal{2*J+1}, MPFR_RNDN);
// 	mpfr::mpreal f12 = (mpfr::mpreal) 4*(J*J+J);
// 	return abs(B2[J+1], MPFR_RNDN) / (f12 * f3);
// }
