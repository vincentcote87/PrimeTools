#include "gtest/gtest.h"
#include "Primetools.h"

#include <iostream>

TEST (PiTest, pi_10) {
  EXPECT_EQ(primetools::getPi(10), 4);
}

TEST (PiTest, pi_100) {
  EXPECT_EQ(primetools::getPi(100), 25);
}

TEST (ThetaTest, theta_10) {
  int_double a = primetools::calculateTheta(10);
  int_double b = log(2*3*5*7);
  long double r = a.right - b.right;
  long double l = a.left - b.left;
  long double tolerance = 0.000000000001;
  EXPECT_TRUE(r <= tolerance && l <= tolerance);
}

TEST (ThetaTest, theta_1) {
  EXPECT_TRUE(primetools::calculateTheta(1).right == 0.0 && primetools::calculateTheta(1).left == 0.0);
}

TEST (PsiTest, psi_10) {
  int_double a = primetools::calculatePsi(10);
  int_double b = log(2*3*2*5*7*2*3);
  long double r = a.right - b.right;
  long double l = a.left - b.left;
  long double tolerance = 0.000000000001;
  EXPECT_TRUE(r <= tolerance && l <= tolerance);
}

TEST (PsiTest, Psi_10) {
  mpfr::mpreal a = primetools::calculatePsiNoTheta(10);
  mpfr::mpreal b = log(2*3*2*5*7*2*3);
  long double variation = 0.0000000001;
  EXPECT_TRUE(a - b <= variation || a - b >= -variation);
}

TEST (LogOverPTest, logOverp_12) {
  mpfr::mpreal ans = 1.530642912;
  mpfr::mpreal testVal = primetools::logpOverp(12);
  long double tolerance = 0.000000001;
  EXPECT_TRUE( testVal - ans <= tolerance);
}

TEST (LogOverPTest, logOverp_11) {
  mpfr::mpreal ans = 1.530642912;
  mpfr::mpreal testVal = primetools::logpOverp(11);
  long double tolerance = 0.000000001;
  EXPECT_TRUE( testVal - ans <= tolerance);
}

TEST (oneOverpTest, oneOverp_25) {
  mpfr::mpreal ans = 1.498956013;
  mpfr::mpreal testVal = primetools::oneOverp(25);
  long double tolerance = 0.000000001;
  std::cout<<testVal<<std::endl;
  EXPECT_TRUE( testVal - ans <= tolerance);
}
