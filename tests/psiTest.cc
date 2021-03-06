#include "gtest/gtest.h"
#include "../include/Primetools.h"
#include "../include/PsiTools.h"

#include <iostream>

TEST (PsiTest, psi_of_2) {
  setupEnvironment();
  EXPECT_EQ(primetools::calculatePsiLongDouble(2), psi(2));
}

TEST (PsiTest, psi_of_1000000) {
  uint64_t x = 1000000;
  long double variation = 0.0000000001;
  EXPECT_TRUE(primetools::calculatePsiLongDouble(x) - psi(x) <= variation || psi(x) - primetools::calculatePsiLongDouble(x) <= variation);
}

TEST (PsiTest, psi_of_100000001) {
  uint64_t x = 100000001;
  long double variation = 0.0000000001;
  EXPECT_TRUE(primetools::calculatePsiLongDouble(x) - psi(x) <= variation || psi(x) - primetools::calculatePsiLongDouble(x) <= variation);
}

TEST (PsiTest, psi_of_0) {
  EXPECT_TRUE(psi(0) == 0);
}
