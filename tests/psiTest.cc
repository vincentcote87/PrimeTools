#include "gtest/gtest.h"
#include "../include/Primetools.h"
#include "../include/PsiTools.h"
#include "../include/s4.h"
#include "../include/mpreal.h"
#include "../include/many.h"

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

TEST (SumTest, constructorTest1) {
  Sum a;
  Sum b(a);
  EXPECT_TRUE(b.get() == 0.0);
}

TEST (SumTest, ConstructorTest2) {
  mpfr::mpreal x = 1.0;
  mpfr::mpreal error = 0.0009;
  Sum a(x, error);
  long double variation = 0.0000000001;
  EXPECT_TRUE(a.get() - 1.0009 <= variation);
}

TEST (SumTest, OperatorTest1) {
  mpfr::mpreal x = 3.5;
  mpfr::mpreal error = 0.0;
  Sum a(x, error);
  a += x;
  long double variation = 0.0000000001;
  EXPECT_TRUE(a.get() - 7.0 <= variation);
}

TEST (SumTest, OpperatorTest2) {
  mpfr::mpreal x = 2.9;
  mpfr::mpreal error = 0.0;
  Sum a(x, error);
  Sum b;
  b = a;
  long double variation = 0.0000000001;
  EXPECT_TRUE(b.get() - 2.9 <= variation);
}

TEST (SumTest, OpperatorTest3) {
  mpfr::mpreal x = 2.9;
  mpfr::mpreal y = 5.1;
  mpfr::mpreal error = 0.0;
  Sum a(x, error);
  Sum b(y, error);
  a += b;
  long double variation = 0.0000000001;
  EXPECT_TRUE(a.get() - 8.0 <= variation);
}

TEST (higherPsiTest, runHigherPsi1) {
  EXPECT_TRUE(higherPsi(0) - 0.0 == 0);
  EXPECT_TRUE(higherPsi(1) - 0.0 == 0);
}

TEST (higherPsiTest, runHigherPsi2) {
  long double variation = 0.0000000001;
  std::cout<<higherPsi(10)<<std::endl;
  // EXPECT_TRUE(higherPsi(10) - 5.347107531 <= variation);
}

TEST (ConsecutiveTest, getDataTest) {
  Consecutive aTable;
  mpfr::mpreal x = 1.25;
  mpfr::mpreal y = 2.87;
  mpfr::mpreal results = 0.0;
  aTable.push_back(x);
  results = aTable.getData(0);
  size_t s = aTable.internalSize();
  EXPECT_TRUE(results == x);
  EXPECT_TRUE(s == 1);
  EXPECT_TRUE(aTable.self(0));
}
